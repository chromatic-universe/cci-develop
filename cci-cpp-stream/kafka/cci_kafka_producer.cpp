//cci_kafka_producer.cpp  william k. johnson 2016

#include "cci_kafka_stream.h"
#include <unistd.h>

using namespace cpp_real_stream;
using namespace rdkafka;

//static initialization
rdkafka::Conf* cci_kafka_producer::topic_conf = rdkafka::Conf::create( rdkafka::Conf::CONF_TOPIC );

//----------------------------------------------------------------------------------------
cci_kafka_producer::cci_kafka_producer( kafka_preamble_ptr ptr_preamble ,
                                        bool events ) : m_preamble { ptr_preamble } ,
                                                        m_tmu(  std::make_unique<time_utils>( stamp_color::green ) ) ,
                                                        m_ptr_rd { nullptr } ,
                                                        m_ptr_topic { nullptr } ,
                                                        m_cur_partition { 0 } ,
                                                        m_b_events { events }
{
            assert( ptr_preamble );

            //library
            config_library_producer();

}
//----------------------------------------------------------------------------------------
cci_kafka_producer::~cci_kafka_producer()
{
        m_tmu->time_stamp();
        std::cerr << "removing kakfa context.....\n";

        if ( m_ptr_rd )
        {
            delete m_ptr_rd;
            m_ptr_rd = nullptr;
        }
        if( m_ptr_topic )
        {
            delete m_ptr_topic;
            m_ptr_topic = nullptr;
        }
        rdkafka::wait_destroyed( 5000 );

 }

//----------------------------------------------------------------------------------------
bool cci_kafka_producer::config_library_producer()
{
        bool b_ret { true };

        //seet delivery report callback
        std::string errstr;
        if( m_preamble->g_config()->set( "dr_cb" ,
                                         m_preamble->mogrifier()->delivery_ptr() ,
                                         errstr ) != rdkafka::Conf::CONF_OK )
        {
            m_tmu->color( stamp_color::red );
            m_tmu->time_stamp();
            std::cerr << errstr
                      << "\n";
            m_tmu->color( stamp_color::green );

            b_ret = false;
        }
        else
        {
            m_tmu->time_stamp();
            std::cerr << "creating library producer....\n";

            std::string errstr;
            m_ptr_rd = rdkafka::Producer::create( m_preamble->g_config() , errstr );
            if ( ! m_ptr_rd )
            {
               m_tmu->color( stamp_color::red );
               m_tmu->time_stamp();
               std::cerr << "failed to create library producer: " << errstr << "\n";
               m_tmu->clear_color();

               b_ret = false;
            }
            else
            {
                m_tmu->time_stamp();
                std::cerr << "cci_kafka_producer valid....."
                              << "\n";
            }
        }

        return b_ret;

}

//----------------------------------------------------------------------------------------
bool cci_kafka_producer::config_topic( const std::string& topic )
{
        bool b_ret  { true };

         m_tmu->time_stamp();
         std::cerr << "configuring topic...."
                   << topic
                   << "\n";

         std::string errstr;
         if( m_ptr_rd )
         {
               m_ptr_topic = rdkafka::Topic::create( m_ptr_rd ,
                                                     topic ,
                                                     topic_conf ,
                                                     errstr );
               if( ! m_ptr_topic )
               {
                   m_tmu->color( stamp_color::red );
                   m_tmu->time_stamp();
                   std::cerr << "failed to create topic: " << errstr << "\n";
                   m_tmu->clear_color();

                   b_ret = false;
               }
               m_str_topic = topic;
        }
        return b_ret;
}

//----------------------------------------------------------------------------------------
void cci_kafka_producer::produce()
{
        m_tmu->time_stamp();
        std::cerr << "producing....\n";

        //read message from stdin
        bool run = true;
        std::string line( "the original corny snaps" );
        for (std::string line; run && std::getline(std::cin, line);)
        {
            if ( line.empty() )
            {
                m_ptr_rd->poll( 0 );
	            continue;
            }

            //produce message
            rdkafka::ErrorCode resp =  m_ptr_rd->produce (  m_ptr_topic ,
                                                            m_cur_partition ,
                                                            rdkafka::Producer::RK_MSG_COPY  ,
                                                            const_cast<char *>(line.c_str( ) ) ,
                                                            line.size() ,
                                                            NULL ,
                                                            NULL );
            if( resp != RdKafka::ERR_NO_ERROR )
            {
                   m_tmu->time_stamp();
                   std::cerr << "produce failed....\n";
            }
            else
            {
                   m_tmu->time_stamp();
                   std::cerr << "% Produced message ("
                             << line.size()
                             << " bytes)\n";
            }
            m_ptr_rd->poll( 0 );
        }
        run = true;

        while ( run && m_ptr_rd->outq_len() > 0)
        {
                m_tmu->time_stamp();
                std::cerr << "waiting for "
                          << m_ptr_rd->outq_len()
                          << "\n";
                m_ptr_rd->poll( 1000 ) ;
        }

}

//----------------------------------------------------------------------------------------
void delivery_report_cb::dr_cb( rdkafka::Message &message )
{
     m_tmu->time_stamp();
     std::cerr << "message delivery for ("
               <<  message.len()
               << " bytes): "
               << message.errstr()
               << "\n";

}

//----------------------------------------------------------------------------------------
void cpp_real_stream::gen_kafka_meta_stream( const std::string& broker ,
                                             const std::string& topic ,
                                             int partition ,
                                             kafka_preamble_ptr preamble )
{
    std::string errstr;
    std::unique_ptr<cci_kafka_producer> producer( new cci_kafka_producer( preamble ) );
    if( !!producer )
    {
       //topic
        if( producer->config_topic( topic ) )
        {
            //etch metadata
            rdkafka::Metadata *metadata;
            rdkafka::ErrorCode err = producer->rd_producer()->metadata(
                                         false , //producer->topic() != nullptr ,
                                         producer->topic() ,
                                         &metadata ,
                                         5000 );
            if( err != rdkafka::ERR_NO_ERROR )
            {
                producer->tutils()->time_stamp();
                std::cerr << "%% failed to acquire metadata: "
                          << rdkafka::err2str( err )
                          << "\n";
            }
            producer->tutils()->time_stamp();
            std::cerr << "acquired topic metadata....\n";

            stream_metadata_header( &std::cerr  , metadata , " kafka server" );
            metadata_stream( &std::cerr , metadata->topics() );
            //metadata_stream( &std::cerr , metadata->brokers() );

       }
    }
}