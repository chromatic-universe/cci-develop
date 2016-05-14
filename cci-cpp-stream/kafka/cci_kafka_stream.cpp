//cpp_kafka_stream.cpp     william k. johnson 2016

#include "cci_kafka_stream.h"

using namespace cpp_real_stream;


//static init
callback_dictionary kf_callback_mogrifier::k_callbacks = { { kafka_callback::kc_sock        , "sock_cb" } ,
                                                           { kafka_callback::kc_open        , "open_cb" } ,
                                                           { kafka_callback::kc_event       ,  "event_cb" } ,
                                                           { kafka_callback::kc_consumer    ,  "consumer_cb" }
                                                         };

//-----------------------------------------------------------------------
std::ostream& operator<< ( std::ostream& ostr , const time_utils& tu )
{
    return ostr << tu.present();
}

//------------------------------------------------------------------------
void kf_callback_mogrifier::perform_event( rdkafka::Event& event )
{

    switch (event.type())
    {
      case RdKafka::Event::EVENT_ERROR:
           m_tym->time_stamp();
          *m_ostr << "ERROR (" << rdkafka::err2str(event.err()) << "): " <<
            event.str() << "\n";
        if (event.err() == rdkafka::ERR__ALL_BROKERS_DOWN)
        {
            m_run = false;
        }
        break;

      case rdkafka::Event::EVENT_STATS:
        m_tym->time_stamp();
        *m_ostr << "\"STATS\": " << event.str() << "\n";
        break;

      case rdkafka::Event::EVENT_LOG:
        if( m_show_log == true )
        {
              m_tym->time_stamp();
             *m_ostr << event.severity()
                     << " "
                     << event.fac().c_str()
                     << " "
                     << event.str().c_str()
                     << "\n";
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

//------------------------------------------------------------------------
void kf_callback_mogrifier::perform_consumption( rdkafka::Message &message , void *opaque )
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
          if ( m_eof ) {
            m_run = false;
          }
          break;
        }

        default:
        {
          std::cerr << "consume failed: " << message.errstr() << std::endl;
          m_run = false;
        }
    }

}

//-----------------------------------------------------------------------
void kf_callback_mogrifier::event_cb( rdkafka::Event &event )
{
    perform_event( event );
}


//-----------------------------------------------------------------------
void kf_callback_mogrifier::consume_cb( rdkafka::Message &message ,  void *opaque )
{
      perform_consumption( message ,  opaque );
}



