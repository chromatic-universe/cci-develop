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


                class cci_stream_event
                {

                            public :

                                //ctors
                                cci_stream_event();
                                explicit cci_stream_event(  kafka_producer_t kpt ,
                                                            stream_event_class sec = stream_event_class::sec_internal );


                                //dtor
                                ~cci_stream_event();


                            private :

                                //attributes
                                kafka_producer_t            m_producer;


                            protected :


                                //


                            public :


                                //accessors-inspectiors
                                kafka_producer_t  producer() { return m_producer; }
                                //mutators
                                void producer( kafka_producer_t kpt ) { m_producer = kpt; }

                };
}


