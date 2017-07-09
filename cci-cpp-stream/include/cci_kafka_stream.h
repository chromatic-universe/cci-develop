#pragma once


//cci
#include <cci_kafka_t.h>
#include <cci_kafka_preamble.hpp>


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
        class cci_kafka_consumer
        {

            public :

                //ctor
                explicit cci_kafka_consumer( kafka_preamble_ptr ptr_preamble ,
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
                    static rdkafka::Conf *topic_conf;

            protected :

                    //attributes
                    kafka_preamble_ptr              m_preamble;
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

                    //immutable
                    static bool         crs_run;
                    static bool         crs_exit_eof;
                    static int          crs_eof_cnt;
                    static int          crs_partition_cnt;
                    static int          crs_verbosity;
                    static long         crs_msg_cnt;
                    static int64_t      crs_msg_bytes;

        };
        //--------------------------------------------------------------------------------
        class cci_kafka_producer
        {

             public :

                //ctor
                explicit cci_kafka_producer( kafka_preamble_ptr ptr_preamble ,
                                             bool events = false );

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
                    virtual void produce( const std::string& messge );


        };

        void gen_kafka_meta_stream( const std::string& broker  ,
                                    const std::string& topic ,
                                    int partition ,
                                    kafka_preamble_ptr preamble = nullptr );



};

namespace crstream = cpp_real_stream;
