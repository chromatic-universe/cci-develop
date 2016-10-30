// cci_kakfka)sinck.c   william k. johnson   2016



//cci
#include <cci_kafka_async_q.h>

static  kafka_context* gkc;


//------------------------------------------------------------------------------------------------
static void init_log();
//------------------------------------------------------------------------------------------------
static void display_banner();



//------------------------------------------------------------------------------------------------
int main( int argc , char* argv[]  )
{
            signal( SIGINT , deactivate );
            signal( SIGTERM , deactivate );


            const char* default_url = "tcp://127.0.0.1:7083";

            int is_daemon = 0;
            if( is_daemon )
            {
                init_log();
                _L( "daemom initialization" , "INFO" , "..cci kafka sink daemon..chromatic universe 2016" );
            }
            else
            {
                display_banner();

                log_fd = stderr;
                _L( "cli initialization" , "INFO" , "..cci kafka sink..chromatic universe 2016" );
                _L( "cli initialization" , "INFO" , "..linux x86-32/64 toolchain using clang 3.71  cc1=gcc 4.9..." );
                _L( "library initialization:.rdkafka version.." , "INFO" , rd_kafka_version_str()  );
            }

            kafka_context kc =
            {
                  ///attributes
                  //
                  //lib context
                  .kafka_ptr = NULL ,
                  //config
                  .conf_ptr = NULL ,
                  //topic config
                  .conf_topic_ptr = NULL ,
                  //topic string
                  .topic_str = "king-console-cci-maelstrom" ,
                  //topic context
                  .topic_ptr = NULL ,
                  //default brokers
                  .brokers = "localhost:9092" ,
                  //group id
                  .group_id = "cci-group" ,
                  //partitions
                  .partitions_ptr = NULL ,
                  //random /partitioner
                  .partition = 0 , //RD_KAFKA_PARTITION_UA ,
                  //devug flags
                  .debug_flags = NULL ,
                  //dumb config
                  .dump_config = 1 ,
                  //running
                  .is_running = 0 ,
                  //eof - false
                  .exit_eof = 0 ,
                  //partition wait eof
                  .wait_eof = 0 ,
                  //queue offset )
                  .start_offset = 0 ,
                  //default mode consumer
                  .mode = 0 ,
                  //command line
                  .argc = argc ,
                  .argv = argv
            };


            gkc = &kc;
            // production context
            _L( "library initialization:" , "INFO" , "...executing production preamble...."  );
            cci_kf_production_preamble( &kc );
            _L( "library initialization.." , "INFO" , "...async server q starting production..." );
            _L( "library initialization..bootstrap servers.." , "INFO" , kc.brokers );
            _L( "library initialization..topic.." , "INFO" ,  kc.topic_str );


            // perform
            if( -1 == kafka_server_q( default_url , &kc ) )
            {
                _L( "async server initialization.." , "ERROR" , "...async server q init failed..aborting" );
            }


            fclose( log_fd );



            return 0;
}

//------------------------------------------------------------------------------------------------
void init_log()
{
        log_fd = fopen( "cci_kafka_sink.log" , "w+" );
        if( log_fd == NULL  )
        {
            fprintf( stderr ,
                     "..could not open log file...\n" );
            exit( 1  );
        }

}

//------------------------------------------------------------------------------------------------
static void display_banner()
{
        char buffer[31];
        memset( buffer ,(int) '*', 30 );
        buffer[30]='\0';
        fprintf( stderr , "%s", buffer );
        fprintf( stderr , "\t\t\t\t\t%s\n", buffer );
        fprintf( stderr ,
                 "\t\t\t%s" ,
                 "cci kafka async q , chromatic universe 2016\n" );
        fprintf( stderr , "%s", buffer );
        fprintf( stderr , "\t\t\t\t\t%s\n\n", buffer );

}


