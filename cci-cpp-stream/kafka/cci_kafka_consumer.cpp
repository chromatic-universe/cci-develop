//cci_kafka_consumer.cpp  william k. johnson 2016

#include "cci_kafka_stream.h"
#include <unistd.h>

using namespace cpp_real_stream;
using namespace rdkafka;


//static initialization
rdkafka::Conf*                      cci_kafka_consumer::topic_conf = rdkafka::Conf::create( rdkafka::Conf::CONF_TOPIC );
bool                                cci_kafka_consumer::crs_run = true;
bool                                cci_kafka_consumer::crs_exit_eof = false;
int                                 cci_kafka_consumer::crs_eof_cnt = 0;
int                                 cci_kafka_consumer::crs_partition_cnt = 0;
int64_t                             cci_kafka_consumer::crs_msg_bytes = 0;
int                                 cci_kafka_consumer::crs_verbosity = 1;
long                                cci_kafka_consumer::crs_msg_cnt = 0;

//----------------------------------------------------------------------------------------
cci_kafka_consumer::cci_kafka_consumer( kafka_preamble_ptr ptr_preamble  ,
                                        bool events ) : m_preamble { ptr_preamble } ,
                                                        m_tmu(  std::make_unique<time_utils>( stamp_color::green )  ) ,
                                                        m_ptr_rd { nullptr } ,
                                                        m_ptr_topic { nullptr } ,
                                                        m_cur_partition { 0 } ,
                                                        m_start_offset { rdkafka::Topic::OFFSET_BEGINNING } ,
                                                        m_b_events { events }
{
        assert( ptr_preamble );

        //library
        config_library_consumer();
}

//---------------------------------------------------------------------------------------
cci_kafka_consumer::~cci_kafka_consumer()
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
bool cci_kafka_consumer::config_library_consumer()
{
        bool b_ret { true };

        m_tmu->time_stamp();
        std::cerr << "creating library consumer....\n";

        std::string errstr;
        m_ptr_rd = rdkafka::Consumer::create( m_preamble->g_config() , errstr );
        if ( ! m_ptr_rd )
        {
           m_tmu->color( stamp_color::red );
           m_tmu->time_stamp();
           std::cerr << "failed to create library consumer: " << errstr << "\n";
           m_tmu->clear_color();

           b_ret = false;
        }
        else
        {
            m_tmu->time_stamp();
            std::cerr << "cci_kafka_consumer valid....."
                          << "\n";
        }

        return b_ret;

}

//----------------------------------------------------------------------------------------
bool cci_kafka_consumer::config_topic( const std::string& topic )
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
void cci_kafka_consumer::consume()
{
       m_tmu->time_stamp();
       std::cerr << "consuming....\n";
       int use_ccb { 1 };


       //start
       rdkafka::ErrorCode resp = m_ptr_rd->start( m_ptr_topic ,
                                                  m_cur_partition ,
                                                  m_start_offset );
       if ( resp != rdkafka::ERR_NO_ERROR )
       {
           m_tmu->color( stamp_color::red );
           m_tmu->time_stamp();
           std::cerr << "failed to start consumer...\n";
           m_tmu->clear_color();
	  
	   return;
       }

       while( m_preamble->run() )
       {
             if( -1 == m_ptr_rd->consume_callback(   m_ptr_topic ,
                                                     0 , //m_cur_partition ,
                                                     1000 ,
                                                     m_preamble->kafka_consume_cb() ,
                                                     &use_ccb ) )
             {
                m_tmu->color( stamp_color::red );
                m_tmu->time_stamp();
                std::cerr << "CONSUMPTION: error in consumption callback....\n";
                m_tmu->clear_color();
             }
             m_ptr_rd->poll( 0 );
       }
       //stop consuming
       m_ptr_rd->stop( m_ptr_topic , m_cur_partition );
       m_ptr_rd->poll( 1000 );

}
