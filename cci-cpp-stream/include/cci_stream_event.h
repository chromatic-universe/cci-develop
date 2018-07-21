//cci_stream_event.h   chromatic universe 2018  william k. johnson



#pragma once


#include <cci_kafka_stream.h>
#include <cci_curl_stream.h>




namespace cpp_real_stream
{

                //aliases
                using kafka_producer_t = cci_kafka_producer*;


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
                    tm_proxy_p_abd_s ,
                    tm_tunnel_p_and_s ,
					tm_http_post_to_queue
				};



                class cci_stream_event
                {

                            public :

                                //ctors
                                cci_stream_event();
                                explicit cci_stream_event(  kafka_producer_t kpt ,
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
                                kafka_producer_t            m_producer;


                            protected :


                                //sttrributes
                                stream_event_class          m_event_class;
                                transport_mechanism         m_transport;


                            public :


                                //accessors-inspectiors
                                kafka_producer_t  producer() { return m_producer; }
                                stream_event_class event_class() const noexcept { return m_event_class; }
                                transport_mechanism transport() const noexcept { return  m_transport; }
                                //mutators
                                void producer( kafka_producer_t kpt ) { m_producer = kpt; }
                                void event_class( const stream_event_class& ec ) { m_event_class = ec; }
                                void transport( const transport_mechanism& tm ) { m_transport = tm; }

                };
}


