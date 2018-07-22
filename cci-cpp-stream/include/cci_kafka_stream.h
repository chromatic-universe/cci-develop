#pragma once


//cci
#include <cci_kafka_t.h>
#include <cci_kafka_preamble.hpp>
#include <unistd.h>



namespace rdkafka = RdKafka;
namespace tclap = TCLAP;

namespace cpp_real_stream
{

        //helpers
        class cci_cli_output : public tclap::StdOutput
        {
            protected :

                std::ostringstream* m_ptr_ostr;
                std::unique_ptr<time_utils> m_tmu;

            public :

                //ctor
                cci_cli_output( std::ostringstream* ostr_ptr ) : m_ptr_ostr { ostr_ptr } ,
                                                           m_tmu( std::make_unique<time_utils>( stamp_color::blue ) )
                {}
                //dtor
                ~cci_cli_output() = default;

                virtual void failure( tclap::CmdLineInterface& c , tclap::ArgException& e );
                virtual void usage( tclap::CmdLineInterface& c );
                virtual void version( tclap::CmdLineInterface& c );
        };

        //services
        //--------------------------------------------------------------------------------
	template<typename T>
        class cci_kafka_consumer
        {

            public :

                //ctor
                cci_kafka_consumer( T ptr_preamble ,
                                     bool events = false );
                //move
                cci_kafka_consumer( cci_kafka_consumer&& ckc ) = default;
                cci_kafka_consumer& operator= ( cci_kafka_consumer&& ckc )  = default;
                //copy
                cci_kafka_consumer( const cci_kafka_consumer& ckc ) = default;
                cci_kafka_consumer& operator= ( const cci_kafka_consumer& ckc ) = default;
                //use unary bool compare
                bool operator!() const { return !m_ptr_rd; }

                //dtor
                virtual ~cci_kafka_consumer();

            private :

                    //helpers
                    bool config_library_consumer();

                    //single topic
                    rdkafka::Conf*  topic_conf;

            protected :

                    //attributes
                    T              		    m_preamble;
                    std::unique_ptr<time_utils>     m_tmu;
                    rd_consumer_ptr                 m_ptr_rd;
                    std::string                     m_str_topic;
                    topic_ptr                       m_ptr_topic;
                    int                             m_cur_partition;
                    int64_t                         m_start_offset;
                    bool                            m_b_events;

            public :

                    //accessors-inspectors
                    rd_consumer_ptr rd_consumer() noexcept { return m_ptr_rd; }
                    std::string topic_str() const noexcept { return m_str_topic; }
                    int64_t start_offset() const noexcept { return m_start_offset; }
                    bool events() const noexcept { return m_b_events; }
                    //mutators
                    void start_offset( const int64_t start ) { m_start_offset = start; }
                    void events( bool ev ) { m_b_events = ev; }

                    //services
                    bool config_topic( const std::string& topic );
                    void consume();


        };

	template<typename T>
	cpp_real_stream::cci_kafka_consumer<T>::cci_kafka_consumer( T  ptr_preamble, bool events ) :
										         topic_conf( rdkafka::Conf::create( rdkafka::Conf::CONF_TOPIC ) ) ,
											 m_preamble { ptr_preamble } ,
											 m_tmu(  std::make_unique<time_utils>( stamp_color::green )  ) ,
											 m_ptr_rd { nullptr } ,
											 m_ptr_topic { nullptr } ,
											 m_cur_partition { 0 } ,
											 m_start_offset { rdkafka::Topic::OFFSET_BEGINNING }
	{
        	assert( ptr_preamble );
        	//library
        	config_library_consumer();
	}
	//
	template<typename T>
	cpp_real_stream::cci_kafka_consumer<T>::~cci_kafka_consumer()
	{
		m_tmu->time_stamp();
		std::cerr << "removing kakfa context.....\n";

		if ( m_ptr_rd )
		{
		    delete m_ptr_rd;
		    m_ptr_rd = nullptr;
		}
		if( m_ptr_topic )
		{
		    delete m_ptr_topic;
		    m_ptr_topic = nullptr;
		}
		rdkafka::wait_destroyed( 5000 );
	}
	//
	template<typename T>
	bool cpp_real_stream::cci_kafka_consumer<T>::config_library_consumer()
	{
		bool b_ret { true };

		m_tmu->time_stamp();
		std::cerr << "creating library consumer....\n";

		std::string errstr;
		m_ptr_rd = rdkafka::Consumer::create( m_preamble->g_config() , errstr );
		if ( ! m_ptr_rd )
		{
		   m_tmu->color( stamp_color::red );
		   m_tmu->time_stamp();
		   std::cerr << "failed to create library consumer: " << errstr << "\n";
		   m_tmu->clear_color();

		   b_ret = false;
		}
		else
		{
		    m_tmu->time_stamp();
		    std::cerr << "cci_kafka_consumer valid....."
				  << "\n";
		}

		return b_ret;

	}
	//
	template<typename T>
	bool cpp_real_stream::cci_kafka_consumer<T>::config_topic( const std::string& topic )
	{
		bool b_ret  { true };

		 m_tmu->time_stamp();
		 std::cerr << "configuring topic...."
			   << topic
			   << "\n";

		 std::string errstr;
		 if( m_ptr_rd )
		 {
		       m_ptr_topic = rdkafka::Topic::create( m_ptr_rd ,
							     topic ,
							     topic_conf ,
							     errstr );
		       if( ! m_ptr_topic )
		       {
			   m_tmu->color( stamp_color::red );
			   m_tmu->time_stamp();
			   std::cerr << "failed to create topic: " << errstr << "\n";
			   m_tmu->clear_color();

			   b_ret = false;
		       }
		       m_str_topic = topic;
		}

		return b_ret;
	}
	//
	template<typename T>
	void cpp_real_stream::cci_kafka_consumer<T>::consume()
	{
	       m_tmu->time_stamp();
	       std::cerr << "consuming....\n";
	       int use_ccb { 1 };


	       //start
	       rdkafka::ErrorCode resp = m_ptr_rd->start( m_ptr_topic ,
							  m_cur_partition ,
							  m_start_offset );
	       if ( resp != rdkafka::ERR_NO_ERROR )
	       {
		   m_tmu->color( stamp_color::red );
		   m_tmu->time_stamp();
		   std::cerr << "failed to start consumer...\n";
		   m_tmu->clear_color();

		   return;
	       }

	       while( m_preamble->run() )
	       {
		     if( -1 == m_ptr_rd->consume_callback(   m_ptr_topic ,
							     m_cur_partition ,
							     1000 ,
							     m_preamble->kafka_consume_cb() ,
							     &use_ccb ) )
		     {
			m_tmu->color( stamp_color::red );
			m_tmu->time_stamp();
			std::cerr << "CONSUMPTION: error in consumption callback....\n";
			m_tmu->clear_color();
		     }
		     m_ptr_rd->poll( 0 );
	       }
	       //stop consuming
	       m_ptr_rd->stop( m_ptr_topic , m_cur_partition );
	       m_ptr_rd->poll( 1000 );

	}




        //--------------------------------------------------------------------------------
        class cci_kafka_producer
        {

             public :

                //ctor
                explicit cci_kafka_producer( kafka_preamble_ptr ptr_preamble ,
                                             bool events = false );
                cci_kafka_producer( const std::string& topic );

                //move
                cci_kafka_producer( cci_kafka_producer&& ckc ) = default;
                cci_kafka_producer& operator= ( cci_kafka_producer&& ckc )  = default;
                //copy
                cci_kafka_producer( const cci_kafka_producer& ckc ) = default;
                cci_kafka_producer& operator= ( const cci_kafka_producer& ckc ) = default;
                //use unary bool compare
                bool operator!() const { return !m_ptr_rd; }

                //dtor
                virtual ~cci_kafka_producer();

             private :

                    //helpers
                    bool config_library_producer();
                    void quick_config_library_producer( const std::string& topic );

                    //single topic
                    static rdkafka::Conf *topic_conf;

             protected :

                    //attributes
                    kafka_preamble_ptr              m_preamble;
                    std::unique_ptr<time_utils>     m_tmu;
                    rd_producer_ptr                 m_ptr_rd;
                    std::string                     m_str_topic;
                    topic_ptr                       m_ptr_topic;
                    int                             m_cur_partition;
                    bool                            m_b_events;
                    rdkafka::Conf*                  m_kafka_conf;

             public :

                    //accessors-inspectors
                    rd_producer_ptr rd_producer() noexcept { return m_ptr_rd; }
                    std::string topic_str() const noexcept { return m_str_topic; }
                    bool events() const noexcept { return m_b_events; }
                    time_utils* tutils() { return m_tmu.get();  }
                    topic_ptr topic() { return m_ptr_topic; }
                    //mutators
                    void events( bool ev ) { m_b_events = ev; }


                    //services
                    bool config_topic( const std::string& topic );
                    virtual void produce();
                    virtual void minimal_produce(  const std::string& message );
                    virtual void produce( const std::string& messge );


        };



        void gen_kafka_meta_stream( const std::string& broker  ,
                                    const std::string& topic ,
                                    int partition ,
                                    kafka_preamble_ptr preamble = nullptr );



};

namespace crstream = cpp_real_stream;
