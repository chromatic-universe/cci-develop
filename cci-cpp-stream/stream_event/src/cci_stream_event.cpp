//cci_stream_event.cpp   chromatic universe 2018  william k. johnso


#include <cci_stream_event.h>


using namespace cpp_real_stream;




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



