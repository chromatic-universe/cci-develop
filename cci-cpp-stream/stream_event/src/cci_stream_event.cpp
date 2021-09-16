//cci_stream_event.cpp   chromatic universe 2018-2021   william k. johnson


#include <cci_stream_event.h>


using namespace cpp_real_stream;
using namespace chromatic_protocol_store;


//-----------------------------------------------------------------------------------------
cci_stream_event::cci_stream_event()
{
}


//-----------------------------------------------------------------------------------------
cci_stream_event::cci_stream_event( kafka_producer_t kpt ,
                                    curl_stream_t cst ,
                                    transport_mechanism tm ,
                                    stream_event_class sec )  try : m_producer { kpt } ,
                                                                    m_curl_stream { cst } ,
                                                                    m_store( std::make_unique<event_protocol_store<cci_curl_stream>>
                                                                     ( m_curl_stream ) ) ,
                                                                    m_event_class { sec } ,
                                                                    m_transport { tm }
{
        assert( kpt );
        assert( cst );
}
catch( const std::exception& err )
{
        std::cerr << "...exception in cci_stream)event consturctuor.."
                  << err.what()
                  << "\n";
}

//-----------------------------------------------------------------------------------------
bool cci_stream_event::post_event_msg_async( const nlohmann::json&  js ,
                                             const std::string& meta_endpoint )
{
        //post parameters
        simplex_dictionary sd = js.get<std::map<std::string,std::string>>();
        //response output if any
        auto ostr = std::make_unique<std::ostringstream>();
        //query object
        auto q = std::make_unique<cps_query>( meta_endpoint , ostr.get() );
        q->simplex( sd );
        //perform
        return store()->perform_naked_post_by_json_async( *q.get() );


}

//-----------------------------------------------------------------------------------------
bool cci_stream_event::dispatch_post_msg( const nlohmann::json& js ,
                                          const std::string& meta_endpoint ,
                                          const bool& async )
{
            bool b_ret { false };

            try
            {
                if ( async  )
                {
                    switch( transport() )
                    {
                        case transport_mechanism::tm_direct_p_and_s :
                        { break; }
                        case transport_mechanism::tm_proxy_p_and_s :
                        { break; }
                        case transport_mechanism::tm_tunnel_p_and_s :
                        { break; }
                        case transport_mechanism::tm_iiop :
                        { break; }
                        default :
                        {
                            b_ret = post_event_msg_async( js , meta_endpoint );
                        }
                    }
                }
            }
            catch( const std::exception& err )
            {
                std::cerr << "..error in event post_dispatch_message->"
                          << err.what()
                          << "\n";

            }

            return b_ret;
}





