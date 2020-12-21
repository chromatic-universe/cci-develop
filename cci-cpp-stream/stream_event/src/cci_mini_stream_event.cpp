//cci_stream_mini_event.cpp  chromatic universe 2208   william k. johnson


#include <cci_mta_kernel.h>
#include <cci_stream_event.h>


using namespace cci_stream_mta;
using namespace cpp_real_stream;
using json = nlohmann::json;
using namespace std::chrono_literals;


int main( int argc , char** argv )
{


             std::shared_ptr<cpp_real_stream::cci_kafka_producer>   producer;
             std::shared_ptr<cpp_real_stream::cci_curl_stream>  adapter_strm;
             std::shared_ptr<cpp_real_stream::cci_stream_event>  stream_event;
             const std::string topic { "mta-stream-kernel-events" };
             const std::string document { "https://localhost:7089/cci_mta_trinity" };
             std::unique_ptr<nlohmann::json> kernel_json = std::make_unique<nlohmann::json>();
             (*kernel_json)["meta-source"] = "mta-stream-kernel-events";
             (*kernel_json)["ecosystem-moniker"] = "mta_kernel";
             (*kernel_json)["peer_uuid"]  = "5a72761c-d9ec-4a3e-8809-d033add87c2e";
             (*kernel_json)["event"] = "mta_ping";
             (*kernel_json)["peer_public"] = "173.69.139.51";

             try
             {
                 if( ! producer ) { producer = std::make_shared<cci_kafka_producer>( topic ); }
                 ACE_DEBUG ( ( LM_DEBUG, "(%P|%t) %M ..initializing event stream ecosystem...curl stream...\n" ) );
                 if( ! adapter_strm ) { adapter_strm = std::make_shared<cci_curl_stream>(); }
                 adapter_strm->debug( true );
                 adapter_strm->https( true );
                 ACE_DEBUG ( ( LM_DEBUG, "(%P|%t) %M ..initializing event stream ecosystem...event store...\n" ) );
                 if( ! stream_event ) { stream_event = std::make_shared<cci_stream_event>(  producer.get() ,
                                                                                            adapter_strm.get() ,
                                                                                            transport_mechanism::tm_http_post_to_queue ,
                                                                                            stream_event_class::sec_internal ); }
                 if( stream_event->dispatch_post_msg( *kernel_json.get() ,
                                           document  + "/post_kernel_stream_msg" ) )
                 {
                      ACE_DEBUG ( ( LM_DEBUG, "(%P|%t) %M ..posted kernel event...\n" ) );
                 }
                 else
                 {
                      ACE_DEBUG ( ( LM_ERROR , "(%P|%t) %M ..could not post ernel event...\n" ) );
                 }

             }
             catch( const std::exception& err  )
             {  ACE_DEBUG ( ( LM_ERROR, "(%P|%t) %M .%s...\n" , err.what() ) ); }

            return 0;
}

