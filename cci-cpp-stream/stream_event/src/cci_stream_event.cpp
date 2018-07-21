//cci_stream_event.cpp   chromatic universe 2018  william k. johnso


#include <cci_stream_event.h>


using namespace cpp_real_stream;




//-----------------------------------------------------------------------------------------
cci_stream_event::cci_stream_event()
{
}


//-----------------------------------------------------------------------------------------
cci_stream_event::cci_stream_event( kafka_producer_t kpt ,
                                    transport_mechanism tm ,
                                    stream_event_class sec ) : m_producer { kpt } ,
                                                               m_event_class { sec } ,
                                                               m_transport { tm }
{
        assert( kpt );
}




