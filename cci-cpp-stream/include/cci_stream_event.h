//cci_stream_event.h   chromatic universe 2018-2021  william k. johnson



#pragma once


#include <cci_kafka_stream.h>
#include <cci_curl_stream.h>
#include <chromatic_protocol_store_t.h>


namespace cpp_real_stream
{

                //forward declarations
                template<typename T , typename T2 =  chromatic_protocol_store::cps_query>
                class event_protocol_store;

                //aliases
                using kafka_producer_t = cci_kafka_producer*;
                using curl_stream_t = cci_curl_stream*;


                //enumerations
                enum class stream_event_class : unsigned long
				{
					sec_external =  0 ,
					sec_internal ,
					sec_supplicant ,
                    sec_plugin ,
					sec_untyped
				};
                //
                enum class transport_mechanism : unsigned long
				{
					tm_direct_p_and_s =  0 ,
                    tm_proxy_p_and_s ,
                    tm_tunnel_p_and_s ,
					tm_http_post_to_queue ,
                    tm_iiop
				};


                //-------------------------------------------------------------------------------------------------------------------
                template<typename T>
                class stream_event_consumer_procedure
                {

                    public :

                        stream_event_consumer_procedure( T meta ) :  m_meta { meta }
                        {
                        }

                    private :

                        //attributes
                        T  			                 m_meta;
                        std::unique_ptr<std::thread> m_runnable;


                    protected :

                        //attributes


                        //dtor
                        virtual ~stream_event_consumer_procedure()
                        {
                            fini();
                        }


                    public :

                        //accessors-inspectors
                        std::string meta() const noexcept { return m_meta; }


                        //services
                        int proc_init();
                        int perform();
                        int fini();

                };

                //services
                template<typename T>
                int  stream_event_consumer_procedure<T>::proc_init()
                {

                    //if( perform() == -1 ) { exit( 0 ); }
                    m_runnable = std::make_unique<std::thread>(
                                           &stream_event_consumer_procedure<T>::perform , this );

                    return 0;
                }


                //
                template<typename T>
                int stream_event_consumer_procedure<T>::perform()
                {
                    m_meta->consume();

                    return 0;
                }

                template<typename T>
                int stream_event_consumer_procedure<T>::fini()
                {
                     m_runnable->join();

                     return 0;
                }



                //-------------------------------------------------------------------------------------------------------------------
                class cci_stream_event
                {

                            public :

                                //ctors
                                cci_stream_event();
                                explicit cci_stream_event(  kafka_producer_t kpt ,
                                                            curl_stream_t cst ,
                                                            transport_mechanism tm = transport_mechanism::tm_http_post_to_queue ,
                                                            stream_event_class sec = stream_event_class::sec_internal );


                                //dtor
                                ~cci_stream_event() = default;


                                //no copy
                                cci_stream_event( const cci_stream_event& ) = delete;
                                cci_stream_event( const cci_stream_event&& ) = delete;
                                //no assign
                                cci_stream_event& operator= ( const cci_stream_event&  ) = delete;
                                cci_stream_event& operator= ( const cci_stream_event&&  ) = delete;


                            private :

                                //attributes
                                kafka_producer_t                                        m_producer;
                                curl_stream_t                                           m_curl_stream;
                                std::unique_ptr<event_protocol_store<cci_curl_stream>>  m_store;


                            protected :


                                //sttrributes
                                stream_event_class          m_event_class;
                                transport_mechanism         m_transport;

                                //helpers
                                bool post_event_msg_async( const nlohmann::json&  js ,
                                                           const std::string& meta_endpoint );



                            public :


                                //accessors-inspectiors
                                kafka_producer_t  producer() { return m_producer; }
                                curl_stream_t  curl_strm() { return m_curl_stream; }
                                stream_event_class event_class() const noexcept { return m_event_class; }
                                transport_mechanism transport() const noexcept { return  m_transport; }
                                event_protocol_store<cci_curl_stream>* store() { return m_store.get(); }
                                //mutators
                                void producer( kafka_producer_t kpt ) { m_producer = kpt; }
                                void curl_strm( curl_stream_t cst ) { m_curl_stream = cst; }
                                void event_class( const stream_event_class& ec ) { m_event_class = ec; }
                                void transport( const transport_mechanism& tm ) { m_transport = tm; }

                                //services
                                bool dispatch_post_msg( const nlohmann::json& js ,
                                                        const std::string& meta_endpoint ,
                                                        const bool& async = true );



                };
                //-------------------------------------------------------------------------------------------------------------------
                template<typename T , typename T2>
                class event_protocol_store : public chromatic_protocol_store::dispatcher_intf<T,T2>
                {

                    public :

                        //ctors
                        event_protocol_store( T* strm ) : m_ptr_stream{ strm } ,
                                              m_result_stream( std::make_unique<std::ostringstream>() )
                        {
                        }


                        explicit event_protocol_store( const std::string& context_param )
                        {}

                        //dtor
                        virtual ~event_protocol_store()
                        {}


                        //no copy
                        event_protocol_store( const event_protocol_store& ) = delete;
                        //no assign
                        const event_protocol_store& operator= ( const event_protocol_store&  ) = delete;


                     private :

                        //attributes
                        std::string 				            m_context_param;
                        T*					                    m_ptr_stream;
                        std::unique_ptr<std::ostringstream>     m_result_stream;


                     protected :

                        //


                     public :


                        //accessors-inspectors }
                        std::string context_param() const noexcept { return m_context_param; }
                        //stream
                        T* stream_ref()
                        { return m_ptr_stream; }
                        //out stream
                        std::ostringstream* out_stream() { return m_result_stream.get(); }



                        //helpes
                        std::string simplex_to_url_query( chromatic_protocol_store::simplex_dictionary& sd );

                        //service interface
                        //------------------------------------------------------------------------------------------
                        bool perform_naked_post_by_json_async( T2& q ,
                                                               chromatic_protocol_store::naked_post_t npt  = nullptr ,
                                                               unsigned future_wait = 1 );
                        //------------------------------------------------------------------------------------------
                      	bool perform_boolean_find_ex( T2& q ,  chromatic_protocol_store::boolean_func_t  bft );
                        //------------------------------------------------------------------------------------------
                        bool perform_boolean_query( T2& q );
                        //------------------------------------------------------------------------------------------
                        void prepare( T2& q )
                        {}

                };

                 //---------------------------------------------------------------------------------
                template<typename T , typename T2>
                std::string event_protocol_store<T,T2>::simplex_to_url_query( chromatic_protocol_store::simplex_dictionary& sd )
                {
                   	const char question { '?' };
                    const char equals { '=' };
                    std::string encoded{ question };
                    unsigned sentinel { 0 };

                    if( !sd.empty() )
                    {
                        for( auto iter : sd )
                            {
                                if( iter.first.length() == 0 )
                                {
                                    sentinel++;
                                    continue;
                                }
                                encoded += iter.first;
                                encoded += equals;
                                encoded += iter.second;

                                sentinel++;
                                if( sentinel == sd.size() )
                                { break; } else { encoded += ","; }
                            }
                    }


                    return encoded;
                }


                //---------------------------------------------------------------------------------
                template<typename T , typename T2>
                bool event_protocol_store<T,T2>::perform_boolean_query( T2& q )
                {

                   	bool b_ret { false };
                    std::string query { simplex_to_url_query( q.simplex() ) };
                    query  = q.url() + "/" + query;
                    std::cerr << "query->" << query << "\n";

                    try
                    {
                        	m_result_stream->str( "" );
                            m_ptr_stream->debug( false );

                            b_ret = m_ptr_stream->execute_base_bool_g( query ,
                                                                       m_result_stream.get() );

                    }
                    catch( const std::exception& err )
                    {
                        std::cerr << err.what()
                                  << "\n";
                    }
                    catch( ... )
                    {
                        std::cerr << "untyped exception...."
                              << "\n";

                    }

                    return b_ret;
                }


                //---------------------------------------------------------------------------------
                template<typename T , typename T2>
                bool event_protocol_store<T,T2>::perform_naked_post_by_json_async( T2& q ,
                                                                                   chromatic_protocol_store::naked_post_t npt ,
                                                                                   unsigned future_wait )
                {
                    //post with parameters
                    bool b_ret { false };
                    nlohmann::json j( q.simplex() );
                    nlohmann::json u( { { "url" , q.url() } } );

                    try
                    {
                        m_result_stream->str( "" );
                        if( m_ptr_stream->results_by_naked_param( j ,
                                                  u ,
                                                  m_result_stream.get() ) )
                        {
                            if( npt )
                            {

                                nlohmann::json rj( m_result_stream.get()->str() );

                                return npt( rj );

                            }
                            b_ret = true;
                        }

                    }
                    catch( std::exception& e )
                    {
                        std::cerr << e.what()
                              << "\n";
                    }

                    return b_ret;

                }

                //---------------------------------------------------------------------------------
                template<typename T , typename T2>
                bool event_protocol_store<T,T2>::perform_boolean_find_ex( T2& q ,
                                                                          chromatic_protocol_store::boolean_func_t  bft )
                {

                    //post with parameters

                    bool b_ret { false };

                    try
                    {
                        m_result_stream->str( "" );

                        if( m_ptr_stream->execute_base_bool_p(  q.url() ,
                                                                simplex_to_url_encoded( q.simplex() ) ,
                                                                m_result_stream.get() ) )
                        {
                            //std::cerr << out_stream();
                            if( bft )
                            {
                                //criterion
                                return bft( (void*) m_result_stream.get() );

                            }
                            b_ret = true;
                        }

                    }
                    catch( std::exception& e )
                    {
                        std::cerr << e.what()
                              << "\n";
                    }
                    catch( ... )
                    {
                        std::cerr << "untyped exception...."
                              << "\n";

                    }

                    return b_ret;

                }



}


