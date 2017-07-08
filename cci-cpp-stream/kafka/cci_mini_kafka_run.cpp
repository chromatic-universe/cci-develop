//cpp_mini_kafka_run,cpp     william k. johnson 2016

#include "cci_kafka_stream.h"
#include <signal.h>

#include <libgen.h>
#include <string.h>
#include <fcntl.h>
using namespace cpp_real_stream;
using namespace rdkafka;

//signals
void sigterm( int sig )
{
    cci_kafka_consumer::crs_run = false;
    std::cerr << "\033[0m\n" ;
    exit( 1 );
}

bool b_events{ false };
static std::pair<std::string,unsigned> split( const std::string& src );


// ----------------------------------------------------------------------------------
int main( int argc , char* argv[] )
{
        //facade wrapper for librdkafka and libzookeeper

        signal( SIGINT  , sigterm );
        signal( SIGTERM , sigterm );


        try
        {
            //boilerplate
            //time utils
            auto tmu( std::make_unique<time_utils>() );
            std::cerr << "\n\t\t\tcci-kafka-stream  ~ chromatic universe 2017\n";



            std::vector<tclap::Arg*>  xorlist;
            xorlist.push_back( cci_kafka_preamble::consumer_switch.get() );
            xorlist.push_back( cci_kafka_preamble::producer_switch.get() );
            xorlist.push_back( cci_kafka_preamble::topic_metadata.get() );
            cci_kafka_preamble::ccmd->xorAdd( xorlist );

            //cli stream
            std::ostringstream ostr;
            ostr << "librdkafka version is "
                 << rdkafka::version_str();
            auto cli( std::make_unique<cci_cli_output>( &ostr ) );
           	cci_kafka_preamble::ccmd->setOutput( cli.get() );
            //parse the argv array.
        	cci_kafka_preamble::ccmd->parse( argc, argv );

            //brokers
            std::string brks { cci_kafka_preamble::the_brokers->getValue() };
            auto pr = split( brks );
            if( pr.first.compare( "nil"  ) == 0 )
            {
                tmu->color( stamp_color::red );
                tmu->time_stamp();
                std::cerr << "..invalid broker specification..\n";
                tmu->time_stamp();
                std::cerr <<  "....<endpoint:port,endpoint:port,...>,..aborting...\n\n";
                tmu->clear_color();

                exit( 1 );
            }
            std::cerr << "\nbroker:\t\t\t"
                      << pr.first
                      << "\n"
                      << "port  :\t\t\t"
                      << pr.second
                      << "\n";
            std::cerr << "---------------------------------------------------------------------------------------\n\n";


            auto brokers( std::make_unique<kafka_brokers>() );
            brokers->emplace_back( std::make_unique<cci_kafka_broker>( pr.first , pr.second , 0 ) );
            //preamble
            auto ckp( std::make_unique<cci_kafka_preamble>( brokers ) );
            //get debug switch
            ckp->events( cci_kafka_preamble::debug_switch->getValue() );

            ckp->init();
            if( !ckp ) { exit( 1 ); }

            tmu->color( stamp_color::green );
            tmu->time_stamp();
            if(  cci_kafka_preamble::consumer_switch->isSet() )
            {
                //consumer
                auto ckc( std::make_unique<cci_kafka_consumer>( ckp.get() , b_events ) );
                if( !!ckc )
                {
                    //topic
                    if( ckc->config_topic( cci_kafka_preamble::topic_name->getValue()) )
                    {
                        ckc->consume();
                    }
                }
            }
            else if( cci_kafka_preamble::producer_switch->isSet() )
            {
                //producer
                auto ckpr( std::make_unique<cci_kafka_producer>( ckp.get() , b_events ) );
                if( !!ckpr )
                {
                    //topic
                    if( ckpr->config_topic( cci_kafka_preamble::topic_name->getValue() ) )
                    {
                        ckpr->produce();
                    }
                }
            }
            else if( cci_kafka_preamble::topic_metadata->isSet() )
            {
                gen_kafka_meta_stream( cci_kafka_preamble::the_brokers->getValue() ,
                                       cci_kafka_preamble::topic_metadata->getValue() ,
                                       0 ,
                                       ckp.get() );
            }
        }
        catch ( tclap::ArgException &e )
        {
            std::cerr << "error: "
                      << e.error()
                      << " for arg "
                      << e.argId()
                      << "\n";
        }


        return 0;

}


// --------------------------------------------------------------------------------------------
std::pair<std::string,unsigned> split( const std::string& src )
{

        const char colon {  ':' };
        std::string str { src };

        try
        {
            std::string::size_type st = src.find_first_of( colon );
            if( st != std::string::npos )
            {

                auto pr = std::make_pair<std::string,unsigned>( src.substr( 0 , st  ),
                                                                stoi( src.substr( st + 1 ) , nullptr , 0 ) ) ;

                return pr;
            }
        }
        catch( ... )
        {
            //
        }

        return std::make_pair<std::string,unsigned>( "nil" , 0 );
}




