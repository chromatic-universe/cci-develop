//cci_kafka_preamble.cpp  william k. johnson 2016

#include "cci_kafka_stream.h"
#include <unistd.h>

using namespace cpp_real_stream;
using namespace rdkafka;


//static initialization
rdkafka::Conf*                      cci_kafka_preamble::gconf = rdkafka::Conf::create( rdkafka::Conf::CONF_GLOBAL );
std::string                         cci_kafka_preamble::crs_metadata_key = "metadata.broker.list";

//command line
std::unique_ptr<cmd_line>           cci_kafka_preamble::ccmd( new tclap::CmdLine ( "cci_mini_kafka_run 2016" , space , "0.12" ) );

//debug
std::unique_ptr<switch_arg>         cci_kafka_preamble::debug_switch( new switch_arg(  "d" ,
                                                                                       "debug" ,
                                                                                       "add debug events to stream" ,
                                                                                       *cci_kafka_preamble::ccmd.get() ,
                                                                                       false
                                                                                    ) );
//consumer
std::unique_ptr<switch_arg>         cci_kafka_preamble::consumer_switch( new switch_arg( "c" ,
                                                                                           "consumer" ,
                                                                                           "place library into consumer mode" ,
                                                                                           true
                                                                                       ) );
//producer
std::unique_ptr<switch_arg>         cci_kafka_preamble::producer_switch( new switch_arg( "p" ,
                                                                                        "producer" ,
                                                                                        "place library into producer mode" ,
                                                                                        true
                                                                                      ) );
//topic
std::unique_ptr<value_arg>         cci_kafka_preamble::topic_name( new value_arg( "t" ,
                                                                                 "topic" ,
                                                                                 "topic for mode" ,
                                                                                  true ,
                                                                                  "" ,
                                                                                  "topic" ,
                                                                                  *cci_kafka_preamble::ccmd.get()
                                                                              ) );
//topic metadata
std::unique_ptr<value_arg>       cci_kafka_preamble::topic_metadata( new value_arg( "m" ,
                                                                                   "metadata" ,
                                                                                   "topic for metadata(empty for all)" ,
                                                                                   false ,
                                                                                   "" ,
                                                                                   "meta"
                                                                                   ) );
//brokers
std::unique_ptr<value_arg>      cci_kafka_preamble::the_brokers( new value_arg( "b" ,
                                                                               "brokers" ,
                                                                               "list of brokers host1:port1,host2:port2,etc," ,
                                                                               true ,
                                                                               "localhost:9092" ,
                                                                               "brokers" ,
                                                                               *cci_kafka_preamble::ccmd.get()
                                                                             ) );

//----------------------------------------------------------------------------------------
cci_kafka_preamble::cci_kafka_preamble( std::unique_ptr<kafka_brokers>& ckb ) : m_tut( std::make_unique<time_utils>( stamp_color::green ) )  ,
                                                        m_mogrifier( std::make_unique<kf_callback_mogrifier>(
                                                              &std::cerr , m_tut , true , false  ) ) ,
                                                        m_b_valid { false }  ,
                                                        m_brokers( std::move( ckb ) ) ,
                                                        m_tmu(  std::make_unique<time_utils>( stamp_color::green ) ) ,

                                                        m_b_events { false }
{
        //
}

//----------------------------------------------------------------
void cci_kafka_preamble::init()
{
        //configure metadata
        config_metadata();

        //set debug mode , all contexts
        if  ( config_debug() )
        {
            //set callbacks
            config_callbacks();
        }

}

//----------------------------------------------------------------------------------------
cci_kafka_preamble::~cci_kafka_preamble()
{
    //
}

//----------------------------------------------------------------------------------------
void cci_kafka_preamble::config_metadata()
{
        std::ostringstream ostr;
        const std::string delim ( "," );

        //<host1:port1,host2:port2,..>
        for( auto& broker : *m_brokers )
        {
            //unpack vector of tuples
            ostr << std::get<to_utype(broker_fields::bf_destination)>( *broker )
                 << ":"
                 << std::get<to_utype(broker_fields::bf_port)>( *broker )
                 << ",";

        }
        std::string broker_str( ostr.str() );
        if( !broker_str.empty() ) {  broker_str.resize( broker_str.size() - 1 ); }

        m_tmu->time_stamp();
        std::cerr << "cci_kafka_preamble constructor....broker<"
                  << broker_str
                  << ">\n";
        m_tmu->time_stamp();
        //set configuration
        std::cerr << "setting configuration properties...."
                  << crs_metadata_key.c_str()
                  << "\n";
        std::string errstr;
        gconf->set( crs_metadata_key.c_str() , broker_str.c_str() , errstr );
        m_tmu->time_stamp();
        std::cerr << "setting debug mode...<all>\n";

}

//----------------------------------------------------------------------------------------
bool cci_kafka_preamble::config_debug()
{
        bool b_ret { true };

        std::string debug( "topic" );
        std::string errstr;
        if ( gconf->set ("debug" , debug , errstr ) != rdkafka::Conf::CONF_OK )
        {
            m_tmu->color( stamp_color::red );
            m_tmu->time_stamp();
            std::cerr << errstr
                      << "\n";
            m_tmu->color( stamp_color::green );

            b_ret = false;
        }

        return b_ret;
}

//----------------------------------------------------------------------------------------
void cci_kafka_preamble::config_callbacks()
{
        //set event callback
        m_tmu->time_stamp();
        std::cerr << "setting event callback....\n";

        std::string errstr;
        //no exit on eof
        m_mogrifier->exit_on_eof( false );
        //events
        m_mogrifier->show_log( m_b_events );
        //run
        m_mogrifier->run( true );
		
	
	std::string cbk_str { kf_callback_mogrifier::k_callbacks[kafka_callback::kc_event] };	
        if(  gconf->set( cbk_str ,
                    dynamic_cast<EventCb*>( m_mogrifier.get() ) ,
                    errstr ) !=  rdkafka::Conf::CONF_OK )
        {
            m_tmu->color( stamp_color::red );
            m_tmu->time_stamp();
            std::cerr << errstr
                      << "\n";
            m_tmu->color( stamp_color::green );
            m_b_valid = false;
        }
        else
        {
            m_tmu->time_stamp();
            std::cerr << "kafka interface initialized.....\n";
            m_b_valid = true;
        }

}




