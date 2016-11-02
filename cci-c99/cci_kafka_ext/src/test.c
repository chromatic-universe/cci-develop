
#include <cci_mini_kafka.h>


void _L( const char* buf , const char* format );
int process_partition_list( partition_list_ptr* partitions  ,
                                                const char*  topics ,
                                                int* wait );

int main( int argc , char* argv[] )
{

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

        cci_kf_production_preamble( &kc );
        cci_kf_retr_topics( &kc );

        fprintf( stderr , "hosts: %s\n" , kc.result );


        return 0;
}


//------------------------------------------------------------------------
int process_partition_list( partition_list_ptr* partitions  ,
                                                const char*  topics ,
                                                int* wait )
{
        // form 1 => <topic1 topic2 etc.> balanced partition
        // form 2 => <topic1:0 topic2:1 etc> statically assigned partition

        int is_subscription = 1;
        char* local_topics = NULL;
        char* vector[10];
        char** atom[2];
        char* tmp = NULL;
        char*  topic = NULL;
        int i = 0;
        int j = 0;
        char *saveptr1;

        local_topics = strdup( topics );
        char* token = (char*) strtok_r( local_topics , " "  , &saveptr1 );
        _L( token , "%s\n" );


        if( token ) { vector[i] = strdup( token ); }
        i++;
        while( token )
        {
            token = (char*) strtok_r( NULL , " " , &saveptr1 );
            if  (NULL == token ) { break; }

            vector[i] = strdup( token );
            _L( token , "%s\n" );
            i++;
        }


        atom[0] = NULL;
        atom[1] =  NULL;
        if( vector[0] )
        {
            for( j = 0; j < i; j++ )
            {
                int32_t partition = -1;
                //if colon delimited pair....
                char* find = (char*) strstr( vector[j] ,  ":"  );
                if( find )
                {
                    if( atom[0] ) { free( atom[0] ); }
                    if( atom[1] ) { free( atom[1] ); }

                    //static partition assignment
                    is_subscription = 0;
                    tmp = (char*) strtok_r( vector[j] , ":" , &saveptr1 );
                    _L( tmp , "%s\n" );
                    atom[0] = (char*) strdup( tmp );
                    tmp = (char*) strtok_r( NULL , ":" , &saveptr1 );
                    _L( tmp , "%s\n" );
                     atom[1] = (char*) strdup( tmp );
                    //partition number
                    partition = atoi( (const char*) atom[1] );
                    topic = (char*) atom[0];
                    wait++;
                }
                else
                {
                    topic = vector[j];
                    _L( topic , "%s\n" );
                }

                //add to partition assignment list
                rd_kafka_topic_partition_list_add( *partitions , topic , partition );
            }
        }

        free( local_topics );
        for ( int x = 0; x < i; x++ )  { free( vector[x] ); }
        if( atom[0] ) { free( atom[0] ); }
        if( atom[1] ) { free( atom[1] ); }


        is_subscription ? fprintf( stderr ,
                                   "configured partitions for %d balanced topic(s)..\n" ,
                                   j ) :
                          fprintf( stderr ,
                                   "configured partitions for %d static topic(s)..\n" ,
                                   j );


        return is_subscription;
}


//------------------------------------------------------------------------
void _L( const char* buf , const char* format )
{
  	struct timeval tv;
	gettimeofday( &tv, NULL );
    fprintf( stderr ,
             "\033[22;34m%u.%03u CCI-MINI-KAFKA-RUN:\033[0m" ,
             (int) tv.tv_sec ,
             (int) ( tv.tv_usec / 1000 ) );
    fprintf( stderr ,
             format ,
             buf  );

}

