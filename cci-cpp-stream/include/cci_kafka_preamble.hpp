//cci_kafka_preamble.hpp  william k. johnson 2017

#pragma once

#include <cci_kafka_t.h>
#include <unistd.h>




namespace cpp_real_stream
{

	        //static init
		static callback_dictionary k_callbacks = { { kafka_callback::kc_sock        , "sock_cb" } ,
							   { kafka_callback::kc_open        , "open_cb" } ,
							   { kafka_callback::kc_event       ,  "event_cb" } ,
							   { kafka_callback::kc_consumer    ,  "consumer_cb" }
						         };
		

		//callback policies
		template<typename T>
		class default_event_callback
		{
				class  kafka_event_cbk : public rdkafka::EventCb 
				{

					public :
					
						kafka_event_cbk() :   m_ostr( &std::cerr) ,
								      m_tym( new time_utils() ) ,
								      m_run{ false } 

						{}

					private :

						//attributes
						std::ostream*                       m_ostr;
						std::unique_ptr<time_utils>         m_tym;
						bool 				    m_run;
					public:
						
						//accessors-inspectors
						std::ostream* stream() { return m_ostr; } 
						bool run() const noexcept { return m_run; }
			
						//mutators
						void stream( std::ostream& ostr ) { m_ostr = ostr; }
						void run( bool b_run ) { m_run = b_run; } 

						void event_cb ( rdkafka::Event &event )
						{
							 switch ( event.type() )
							 {
							      case RdKafka::Event::EVENT_ERROR:
								  m_tym->time_stamp();
								  *m_ostr << "ERROR (" << rdkafka::err2str(event.err()) << "): " <<
								    event.str() << "\n";
								  if( event.err() == rdkafka::ERR__ALL_BROKERS_DOWN )
                                                                  { m_run = false; }
								break;

							      case rdkafka::Event::EVENT_STATS :
							      {
								m_tym->time_stamp();
								*m_ostr << "STATS("
									<< event.str()
									<< ")\n";
								break;
							      }	
							      case rdkafka::Event::EVENT_LOG:
							      {
								      m_tym->time_stamp();
								     *m_ostr << "LOG("
									     <<  event.severity()
									     << ") "
									     << event.fac().c_str()
								     << " "
								     << event.str().c_str()
								     << ")\n";
							      }
							      break;

							      default:
								m_tym->time_stamp();
								*m_ostr << "EVENT " << event.type() <<
								    " (" << rdkafka::err2str(event.err()) << "): " <<
								    event.str() << std::endl;
								break;
							    }

						}
				};
						
		
			public :
			
				
				default_event_callback() : m_cbk( std::make_unique<kafka_event_cbk>() )
				{}


			protected :

				~default_event_callback()
				{}
				
				//attributes
				T context;
				std::unique_ptr<kafka_event_cbk> m_cbk;
				

			public :

				//accessors-inspectors
			 	rdkafka::EventCb* kafka_event_cb() { return m_cbk.get(); }
								
				
				
		};
		//
		template<typename T>
		class default_consumer_callback
		{
				class  kafka_consumer_cbk : public rdkafka::ConsumeCb 
				{

					public :
					
						kafka_consumer_cbk() :   m_ostr( &std::cerr) ,
								         m_tym( new time_utils() ) ,
									 m_run{ false } 
						{}

					private :

						//attributes
						std::ostream*                       m_ostr;
						std::unique_ptr<time_utils>         m_tym;
						bool 				    m_run;


					public:
						
						//accessors-inspectors
						std::ostream* stream() { return m_ostr; } 			
						bool run() const noexcept { return m_run; }

						//mutators
						void stream( std::ostream& ostr ) { m_ostr = ostr; }
						void run( bool b_run ) { m_run = b_run; } 

						
						//services
						void consume_cb( rdkafka::Message &message ,  void *opaque )
						{
						    switch ( message.err() )
						    {
							case rdkafka::ERR__TIMED_OUT:
							  break;

							case rdkafka::ERR_NO_ERROR:
							{
							  //real message
							  m_tym->color( stamp_color::blue );
							  m_tym->time_stamp();
							  std::cerr << "MESSAGE read msg at offset "
								       << message.offset()
							       << "\n";
							  if ( message.key() )
							  {
							    m_tym->time_stamp();
							    std::cerr << "key: "
								      << message.key() << std::endl;
							  }
							  m_tym->time_stamp();
							  std::cerr << "message-len:"
								    <<  message.len()
								    << " "
								    <<  static_cast<const char *>( message.payload() )
								    << "\n";
							  m_tym->color( stamp_color::green );

							  break;
							}
							case rdkafka::ERR__PARTITION_EOF:
							{
							  //last message
							  //if ( m_eof ) {
							  //  m_run = false;
							  break;
							}

							default:
							{
							  std::cerr << "consume failed: " << message.errstr() << std::endl;
							  m_run = false;
							}
					    	 }
					}
				};
						
		
			public :
			
				
				default_consumer_callback() : m_cbk( std::make_unique<kafka_consumer_cbk>() )
				{}


		

			protected :

				~default_consumer_callback()
				{}
				
				//attributes
				T context;
				std::unique_ptr<kafka_consumer_cbk> m_cbk;
				

			public :

				//accessors-inspectors
			 	rdkafka::ConsumeCb* kafka_consume_cb() { return m_cbk.get(); }
								
				
				
		};
		//
		template<typename T>
		class default_delivery_callback
		{
				class  kafka_delivery_cbk : public rdkafka::DeliveryReportCb 
				{

					public :
					
						kafka_delivery_cbk() :   m_ostr( &std::cerr) ,
								         m_tym( new time_utils() ) ,
									 m_run{ false } 
						{}

					private :

						//attributes
						std::ostream*                       m_ostr;
						std::unique_ptr<time_utils>         m_tym;
						bool 				    m_run;


					public:
						
						//accessors-inspectors
						std::ostream* stream() { return m_ostr; } 			
						bool run() const noexcept { return m_run; }

						//mutators
						void stream( std::ostream& ostr ) { m_ostr = ostr; }
						void run( bool b_run ) { m_run = b_run; } 

						
						//services
						void dr_cb( rdkafka::Message &message )
						{
						    switch ( message.err() )
						    {
							case rdkafka::ERR__TIMED_OUT:
							  break;

							case rdkafka::ERR_NO_ERROR:
							{
							  //real message
							  m_tym->color( stamp_color::blue );
							  m_tym->time_stamp();
							  std::cerr << "MESSAGE read msg at offset "
								       << message.offset()
							       << "\n";
							  if ( message.key() )
							  {
							    m_tym->time_stamp();
							    std::cerr << "key: "
								      << message.key() << std::endl;
							  }
							  m_tym->time_stamp();
							  std::cerr << "message-len:"
								    <<  message.len()
								    << " "
								    <<  static_cast<const char *>( message.payload() )
								    << "\n";
							  m_tym->color( stamp_color::green );

							  break;
							}
							case rdkafka::ERR__PARTITION_EOF:
							{
							  //last message
							  //if ( m_eof ) {
							  //  m_run = false;
							  break;
							}

							default:
							{
							  std::cerr << "consume failed: " << message.errstr() << std::endl;
							  m_run = false;
							}
					    	 }
					}
				};
						
		
			public :
			
				
				default_delivery_callback() : m_cbk( std::make_unique<kafka_delivery_cbk>() )
				{}


		

			protected :

				~default_delivery_callback()
				{}
				
				//attributes
				T context;
				std::unique_ptr<kafka_delivery_cbk> m_cbk;
				

			public :

				//accessors-inspectors
			 	rdkafka::DeliveryReportCb* kafka_delivery_cb() { return m_cbk.get(); }
								
				
				
		};

		//--------------------------------------------------------------------------------
		template <
				typename T ,     
				template<class> class event_callback_policy ,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
			 >
		class cci_kafka_preamble : public event_callback_policy<T> ,
					   public consumer_callback_policy<T> ,
					   public delivery_callback_policy<T>
		{

		    public :

			//ctor
			explicit cci_kafka_preamble( std::unique_ptr<kafka_brokers>& ckb ) : m_b_valid { false }  ,
                                                                                             m_eof { false } ,
											     m_run { false } ,
											     m_brokers( std::move( ckb ) ) ,
	  										     m_tmu(  std::make_unique<time_utils>( stamp_color::green ) ) ,
										  	     m_b_events { false }
			{}

			cci_kafka_preamble( cci_kafka_preamble&& ckc ) = default;
			cci_kafka_preamble& operator= ( cci_kafka_preamble&& ckc ) = default;
			//copy
			cci_kafka_preamble( const cci_kafka_preamble& ckc ) = default;
			cci_kafka_preamble& operator= ( const cci_kafka_preamble& ckc ) = default;
			//use unary bool compare
			bool operator!() const { return !m_b_valid; }

			//dtor
			//------------------------------------------------d---------------------------------------
			virtual ~cci_kafka_preamble()
			{}

		    private :

			//attributes
			bool m_b_valid;
			bool m_eof;
			bool m_run;

			//helpers			
			//----------------------------------------------------------------------------------------
			void config_metadata()
			{
				std::ostringstream ostr;
				const std::string delim ( "," );

				//<host1:port1,host2:port2,..>
				for( auto& broker : *m_brokers )
				{
				    //unpack vector of tuples
				    ostr << std::get<to_utype(broker_fields::bf_destination)>( *broker )
					 << ":"
					 << std::get<to_utype(broker_fields::bf_port)>( *broker )
					 << ",";

				}
				std::string broker_str( ostr.str() );
				if( !broker_str.empty() ) {  broker_str.resize( broker_str.size() - 1 ); }

				m_tmu->time_stamp();
				std::cerr << "cci_kafka_preamble constructor....broker<"
					  << broker_str
					  << ">\n";
				m_tmu->time_stamp();
				//set configuration
				std::cerr << "setting configuration properties...."
					  << crs_metadata_key.c_str()
					  << "\n";
				std::string errstr;
				gconf->set( crs_metadata_key.c_str() , broker_str.c_str() , errstr );
				m_tmu->time_stamp();
				std::cerr << "setting debug mode...<all>\n";

			}

			//----------------------------------------------------------------------------------------
			bool config_debug()
			{
				bool b_ret { true };

				std::string debug( "topic" );
				std::string errstr;
				if ( gconf->set ("debug" , debug , errstr ) != rdkafka::Conf::CONF_OK )
				{
				    m_tmu->color( stamp_color::red );
				    m_tmu->time_stamp();
				    std::cerr << errstr
					      << "\n";
				    m_tmu->color( stamp_color::green );

				    b_ret = false;
				}

				return b_ret;
			}

			//----------------------------------------------------------------------------------------
			void config_callbacks()
			{
				//set event callback
				m_tmu->time_stamp();
				std::cerr << "setting event callback....\n";

				std::string errstr;
				//no exit on eof
				exit_on_eof( false );
				run( true );
					
				//set event callback
				std::string cbk_str { k_callbacks[kafka_callback::kc_event] };	
				if(  gconf->set( cbk_str ,
					    	this->kafka_event_cb() ,
					    errstr ) !=  rdkafka::Conf::CONF_OK )
				{
				    m_tmu->color( stamp_color::red );
				    m_tmu->time_stamp();
				    std::cerr << errstr
					      << "\n";
				    m_tmu->color( stamp_color::green );
				    m_b_valid = false;
				}
				else
				{
				    m_tmu->time_stamp();
				    std::cerr << "kafka interface initialized.....\n";
				    m_b_valid = true;
				}

			}

			//rdkafka
			static rdkafka::Conf *gconf ;

		    protected :

			//attributes
			std::unique_ptr<kafka_brokers>  m_brokers;
			std::unique_ptr<time_utils>     m_tmu;
			bool                            m_b_events;

		    public :

			//accessors-inspectors
			brokers_ptr brokers()  noexcept { return m_brokers.get(); }
			static rdkafka::Conf* g_config() { return gconf; }
			bool exit_on_eof() { return m_eof; }
			bool run() { return m_run; }
			

			//mutators
			void events( bool ev ) { m_b_events = ev; }
			void exit_on_eof( bool eof ) { m_eof = eof; }
			void run( bool rn ) { m_run = rn; }

			//ummutable
			static std::string  crs_metadata_key;
			//cli
			static std::unique_ptr<tclap::CmdLine> ccmd;
			//immutable cli
			static std::unique_ptr<switch_arg>          debug_switch;
			static std::unique_ptr<switch_arg>          consumer_switch;
			static std::unique_ptr<switch_arg>          producer_switch;
			static std::unique_ptr<value_arg>           topic_name;
			static std::unique_ptr<switch_arg>          topic_metadata;
			static std::unique_ptr<value_arg>           the_brokers;

			//services
			//----------------------------------------------------------------
			void init()
			{
				//configure metadata
				config_metadata();

				//set debug mode , all contexts
				if  ( config_debug() )
				{
				    //set callbacks
				    config_callbacks();
				}

				run( true );

			}


		};


		typedef cci_kafka_preamble<
                                           placeholder,
                                           default_event_callback ,
					   default_consumer_callback ,
					   default_delivery_callback
                                          >  kafka_default_preamble;
		using kafka_preamble_ptr = kafka_default_preamble*;


		//static initialization-this verbosity seems unavoidable
	        template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy,
				template<class> class delivery_callback_policy
		         >
                rdkafka::Conf* cci_kafka_preamble<T ,
                                                  event_callback_policy ,
                                                  consumer_callback_policy ,
                                                  delivery_callback_policy>::gconf = rdkafka::Conf::create( rdkafka::Conf::CONF_GLOBAL );
		template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
		         >
                std::string cci_kafka_preamble<T , 
                                               event_callback_policy ,
                                               consumer_callback_policy ,
                                               delivery_callback_policy>::crs_metadata_key = "metadata.broker.list";

		//command line
		template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy 
		         >
                std::unique_ptr<cmd_line> cci_kafka_preamble<T,
                                                             event_callback_policy ,
                                                             consumer_callback_policy ,
                                                             delivery_callback_policy>::ccmd( new cmd_line ( "cci_mini_kafka_run 2016" ,
                                                                                                                 space , 
                                                                                                                "0.12" ) );

		//debug
		template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
		         >
                std::unique_ptr<switch_arg> cci_kafka_preamble<T ,
							       event_callback_policy ,
                                                               consumer_callback_policy ,
                                                               delivery_callback_policy>::debug_switch( new switch_arg(  "d" ,
												       "debug" ,
												       "add debug events to stream" ,
												       *cci_kafka_preamble::ccmd.get() ,
												       false
												    ) );
		//consumer
		template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
		        >
                std::unique_ptr<switch_arg> cci_kafka_preamble<T , 
                                                               event_callback_policy ,
                                                               consumer_callback_policy ,
                                                               delivery_callback_policy>::consumer_switch( new switch_arg( "c" ,
													   "consumer" ,
													   "place library into consumer mode" ,
													   true
												       ) );
		//producer
		template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
			 >
                std::unique_ptr<switch_arg> cci_kafka_preamble<T , 
                                                               event_callback_policy ,
                                                               consumer_callback_policy ,
                                                               delivery_callback_policy>::producer_switch( new switch_arg( "p" ,
													"producer" ,
													"place library into producer mode" ,
													true
												      ) );

		//topic metadata
		template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
			 >
                std::unique_ptr<switch_arg> cci_kafka_preamble<T ,
                                                               event_callback_policy ,
                                                               consumer_callback_policy ,
                                                               delivery_callback_policy>::topic_metadata( new switch_arg( "m" ,
												   "metadata" ,
												   "topic for metadata(empty for all)" ,
												   true
												   ) );

		//topic
		template <
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
			 >
                std::unique_ptr<value_arg> cci_kafka_preamble<T , 
                                                              event_callback_policy ,
                                                              consumer_callback_policy ,
                                                              delivery_callback_policy>::topic_name( new value_arg( "t" ,
												 "topic" ,
												 "topic for mode" ,
												  false ,
												  "" ,
												  "topic" ,
												  *cci_kafka_preamble::ccmd.get()
											      ) );


	        template<
				typename T ,     
				template<class> class event_callback_policy,
				template<class> class consumer_callback_policy ,
				template<class> class delivery_callback_policy
			 >
		std::unique_ptr<value_arg>   cci_kafka_preamble<T , 
                                                                event_callback_policy ,
                                                                consumer_callback_policy ,
                                                                delivery_callback_policy>::the_brokers( new value_arg( "b" ,
												       "brokers" ,
												       "list of brokers host1:port1,host2:port2,etc," ,
												       true ,
												       "localhost:9092" ,
												       "brokers" ,
												       *cci_kafka_preamble::ccmd.get()
												     ) );



	
}


