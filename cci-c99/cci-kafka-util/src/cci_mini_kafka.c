//cci_mini_kafka.c   chromatic universe   william k. johnson 2018

#include <cci_mini_kafka.h>


static kafka_context_ptr  context = NULL;

int quiet = 0;
int run = 1;
int exit_eof = 0;

typedef  cci_cli_dictionary* cli_dictionary_t;


//locals
//------------------------------------------------------------------------
//signals
static void sig_usr1 ( int sig );
//------------------------------------------------------------------------
//helpers
//
//stream usage
static void stream_out_usage( const char* binary );
//------------------------------------------------------------------------
//describe groups
static int describe_groups ( rd_kafka_t *rk , const char *group ) ;
//------------------------------------------------------------------------
//partitions
static int process_partition_list( partition_list_ptr* partitions ,
                                   const gchar*  topics ,
                                   int* wait ,
                                   int offset );
//------------------------------------------------------------------------
//rebalance stream
void stream_out_partition_list ( FILE *fp ,
                                 int is_assigned ,
                                 const rd_kafka_topic_partition_list_t *partitions);
//------------------------------------------------------------------------
//producer
static void ex_parte_producer( kafka_context_ptr kc );
//------------------------------------------------------------------------
//consumer
static void ex_parte_consumer( kafka_context_ptr kc );
//metadatar
static void ex_parte_metadata( kafka_context_ptr kc );
//------------------------------------------------------------------------
static void make_kafka_handle( kafka_context_ptr kc  );
//------------------------------------------------------------------------
static void make_kafka_logger( kafka_context_ptr kc );
//------------------------------------------------------------------------
static void metadata_set( kafka_context_ptr kc );
//------------------------------------------------------------------------
static void metadata_set_ex( kafka_context_ptr kc );
//------------------------------------------------------------------------
static void debug_set( conf_k_ptr ptr , const char* contexts );
//------------------------------------------------------------------------
static void _L( const char* buf , const char* format );
//------------------------------------------------------------------------
static void configuration_dump( kafka_context_ptr kc );


//external
//callbacks
//------------------------------------------------------------------------
void cci_kf_logger ( const rd_kafka_t* ptr_handle ,
                     int level ,
           	         const char* fac ,
                     const char* buf );
//------------------------------------------------------------------------
//message delivered
void cci_kf_msg_delivered( rd_kafka_t* rk ,
                           const rd_kafka_message_t* rkmessage ,
                           void_ptr opaque )
{
     //called once for each message
    if( rkmessage->err )
    {
        fprintf( stderr ,
                 "%% message delivery failed: %s\n"  ,
                 rd_kafka_message_errstr( rkmessage )
               );
    }
    else
    {
        fprintf( stderr,
                 "%% message delivered ( %zd bytes , offset %"PRId64", "
                                         "partition % "PRId32" )\n" ,
                 rkmessage->len ,
                 rkmessage->offset ,
                 rkmessage->partition
               );

    }

}

//------------------------------------------------------------------------
//message consume
void cci_kf_msg_consume( kafka_context_ptr kc ,
                         message_ptr_k rkmessage ,
                         void_ptr opaque )
{
           if( rkmessage->err )
           {
                if( rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF )
                {
                    _L( "" , "%s" );
                    fprintf( stderr ,
                             "consumer reached end of %s [%"PRId32"] "
                             "message queue at offset %"PRId64"\n",
                             rd_kafka_topic_name( rkmessage->rkt ) ,
                             rkmessage->partition, rkmessage->offset );

                    if ( kc->exit_eof && --kc->wait_eof == 0)
                    {
                                        fprintf (stderr,
                                                "%% All partition(s) reached EOF: "
                                                "exiting\n" );
                                                 kc->is_running = 0;
                     }

                     return;
                 }
                 //
                 if ( rkmessage->rkt )
                 {
                        fprintf(stderr, "%% Consume error for "
                                "topic \"%s\" [%"PRId32"] "
                                "offset %"PRId64": %s\n",
                                rd_kafka_topic_name(rkmessage->rkt),
                                rkmessage->partition,
                                rkmessage->offset,
                                rd_kafka_message_errstr(rkmessage));

                 }
                 else
                 {
                        fprintf(stderr, "%% Consumer error: %s: %s\n",
                                rd_kafka_err2str(rkmessage->err),
                                rd_kafka_message_errstr(rkmessage));
                 }

                 if (rkmessage->err == RD_KAFKA_RESP_ERR__UNKNOWN_PARTITION ||
                    rkmessage->err == RD_KAFKA_RESP_ERR__UNKNOWN_TOPIC)
                    {   run = 0; }

                return;
            }

            fprintf( stdout ,
                    "%% Message (topic %s [%"PRId32"], "
                    "offset %"PRId64", %zd bytes):\n" ,
                    rd_kafka_topic_name (rkmessage->rkt  ),
                    rkmessage->partition,
                    rkmessage->offset ,
                    rkmessage->len );

            if (rkmessage->key_len) {
                if (output == OUTPUT_HEXDUMP)
                    kc->cci_hex_dump(stdout, "Message Key",
                        rkmessage->key, rkmessage->key_len);
                else
                    printf("Key: %.*s\n",
                           (int)rkmessage->key_len, (char *)rkmessage->key);
            }
            if( kc->hex_out == OUTPUT_HEXDUMP )
            {
                kc->cci_hex_dump( stdout ,
                                  "Message Payload" ,
                                rkmessage->payload ,
                                rkmessage->len );
            }
            else
            {
                printf( "%.*s\n",
                        (int) rkmessage->len ,
                        (char *) rkmessage->payload );
            }

}


//------------------------------------------------------------------------
//partition rebalance
void cci_kf_rebalance_cb ( rd_kafka_t *rk,
                           rd_kafka_resp_err_t err ,
			               rd_kafka_topic_partition_list_t *partitions ,
                           void *opaque )
{
    _L( "" , "%s" );
	fprintf( stderr ,
             "consumer group rebalanced.....\n");


	switch ( err )
	{
        case RD_KAFKA_RESP_ERR__ASSIGN_PARTITIONS:
             _L( "" , "%s" );
            fprintf(stderr, "assigned:");
            stream_out_partition_list( stderr ,
                                       1 ,
                                       partitions );
            rd_kafka_assign( rk, partitions );

            break;

        case RD_KAFKA_RESP_ERR__REVOKE_PARTITIONS:
            _L( "" , "%s" );
            fprintf(stderr, "revoked:");
            stream_out_partition_list( stderr ,
                                       0 ,
                                       partitions );
            rd_kafka_assign( rk , NULL );
            break;

        default:
            _L( "" , "%s" );
            fprintf( stderr ,
                     "failed: %s\n",
                     rd_kafka_err2str( err ) );
            break;
	}
}


//------------------------------------------------------------------------
void cci_kf_hex_dump( file_ptr fp ,
                      const char *name ,
                      const void_ptr ptr ,
                      size_t len )
{
     const char* p = (const char*) ptr;
	 unsigned int of = 0;

 	 if( name ) { fprintf( fp , "%s hexdump (%zd bytes):\n" , name , len ); }

     //hex
     for ( of = 0; of < len; of += 16 )
     {
         char hexen[16*3+1];
		 char charen[16+1];
		 int hof = 0;

		 int cof = 0;
		 int i;

		 for( i = of; i < of + 16 && i < len; i++ )
         {
			hof += sprintf( hexen + hof ,
                            "%02x " ,
                            p[ i ] & 0xff );
			cof += sprintf( charen + cof ,
                            "%c" ,
				            isprint( (int)p[i] ) ? p[i] : '.' );
		 }
		 fprintf( fp ,
                  "%08x: %-48s %-16s\n" ,
		      	  of ,
                  hexen ,
                  charen );
     }//end hex

}

//------------------------------------------------------------------------
void cci_kf_metadata_print ( const char *topic ,  const struct rd_kafka_metadata *metadata  )
{
     int i, j, k;

     printf( "\033[1;37mmetadata for %s (from broker %"PRId32": %s):\n" ,
              topic ? : "all topics" ,
              metadata->orig_broker_id ,
              metadata->orig_broker_name );

     //iterate brokers
     printf( " %i brokers:\n", metadata->broker_cnt );
     for ( i = 0 ; i < metadata->broker_cnt ; i++ )
     {
              printf( "  broker %"PRId32" at %s:%i\n",
                         metadata->brokers[i].id ,
                         metadata->brokers[i].host ,
                         metadata->brokers[i].port );
     }//end brokers
     //iterate topics
      printf(" %i topics:\n", metadata->topic_cnt);
      for( i = 0; i < metadata->topic_cnt; i++ )
      {
                const metadata_topic_ptr_k t = &metadata->topics[i];
                printf( " \033[0;37mtopic \"%s\" with %i partitions:\033[0m" ,
                        t->topic,
                        t->partition_cnt );

                        if( t->err )
                        {
                            printf( " %s" , rd_kafka_err2str( t->err) );
                            if ( t->err == RD_KAFKA_RESP_ERR_LEADER_NOT_AVAILABLE ) { printf(" (try again)" ); }
                        }
                printf( "\n" );
                //iterate through topic's partitions
                for( j = 0; j < t->partition_cnt; j++ )
                {
                        const metadata_partition_ptr_k p = &t->partitions[j];
                        printf( "    partition %"PRId32", "
                                "leader %"PRId32", replicas: ",
                                p->id ,
                                p->leader );

                        //iterate partition's replicas
                        for( k = 0; k < p->replica_cnt; k++ )
                        {
                            printf( "%s%"PRId32 ,
                                    k > 0 ? ",":"", p->replicas[k] );
                        }//end replicas

                        //iterate partition's isr(s)
                        printf(", isrs: ");
                        for( k = 0; k < p->isr_cnt ; k++ )
                        {
                                printf("%s%"PRId32,
                                       k > 0 ? ",":"", p->isrs[k]);
                        }//end isr(s)
                        if ( p->err ) { printf( ", %s\n", rd_kafka_err2str( p->err ) ); }
                        else { printf( "\n" ); }

                }//end topic partitions
      }//end topics
      printf( "\031[0m" );
}

//------------------------------------------------------------------------
void cci_kf_mini_run( kafka_context_ptr kc )
{

	     int opt;
	     quiet = !isatty( STDIN_FILENO );
         cli_dictionary_t  cdt = cci_cli_dictionary_new();


	     while ( ( opt = getopt( kc->argc ,
				     kc->argv ,
				     "PCLDt:d:p:b:o:g:xzevh" ) ) != -1 )
	     {
             switch( opt )
             {
                ///modes
                //producer
                case 'P' :
                //consumer
                case 'C' :
                //group description
                case 'D' :
                //metadata list mode
                case 'L' :
                //message transfer agent streams
                case 'M' :
                if( kc->mode )
                {
                    _L( "mode has already been set..." , "%s\n" );
                    exit( 1 );
                }
                kc->mode = opt;
                cci_cli_dictionary_add( cdt , "mode" , &opt );
                break;

                //exit eof
                case 'e':
                        kc->exit_eof = 1;
                        cci_cli_dictionary_add( cdt , "exit_eof" , &opt );
                        break;
                //topic
                case 't' :
                        kc->topic_str = strdup( optarg );
                        cci_cli_dictionary_add( cdt , "topic" , &opt );
                        break;
                //partition
                case 'p':
                        kc->partition = atoi( optarg );
                        cci_cli_dictionary_add( cdt , "partition" , &opt );
                        break;
                //brokers
                case 'b' :
                        kc->brokers = strdup( optarg );
                        cci_cli_dictionary_add( cdt , "brokers" , &opt );
                        break;
                //group
                case 'g' :
                        kc->group_id = strdup( optarg );
                        cci_cli_dictionary_add( cdt , "group" , &opt );
                        break;
                //debug
                case 'd' :
                        kc->debug_flags = optarg;
                        cci_cli_dictionary_add( cdt , "debug" , &opt );
                        break;
                //dump configuration
                case 'x' :
                        kc->dump_config = 1;
                        break;
                //hex
                case 'z' :
                        kc->hex_out = OUTPUT_HEXDUMP;
                        break;
                //consumption offset
                case 'o':
                        kc->start_offset = atoi( optarg );
                        break;
                case 'v':
                        fprintf( stderr , "\033[22;32mcci_kafka_plex version 0.91 chromatic universe , william k. johnson 2018\n\033[0m" );
                        exit( 0 );
                case 'h' :
                default :
                {
                    //executable moniker as arg
                    stream_out_usage( kc->argv[0] );
                    exit( 0 );
                }
             }

	     }

	     if( kc->dump_config )
	     {
             kc->conf_ptr = rd_kafka_conf_new();
             kc->conf_topic_ptr = rd_kafka_topic_conf_new();

             configuration_dump( kc );

             if( !kc->mode ) { exit( 0 ); }
	     }


	     //producer
	     if( kc->mode == 0 )

	     {
                stream_out_usage( kc->argv[0] );
		        _L(  "\033[0;31mmode must be specified...\n\033[0m" , "%s\n"  );

		        exit( 1 );
	     }
	     if( kc->mode == 'P' )
	     {

            if(  ( kc->topic_str == NULL ) || ( kc->brokers == NULL ) )
            {
                stream_out_usage( kc->argv[0] );
                _L(  "\033[0;31merror in producer mode: topic and brokers must be specified....\n\033[0m" , "%s\n" );
                exit( 1 );
            }

		    ex_parte_producer( kc );
	     }
	     else if( ( kc->mode == 'C' ) || ( kc->mode == 'D' ) )
	     {

            if(  ( kc->topic_str == NULL ) ||
                 ( kc->brokers == NULL )   ||
                 ( kc->group_id == NULL ) )
            {
                stream_out_usage( kc->argv[0] );
                _L(  "\033[0;31merror in consume mode: topic , group id and brokers must be specified....\033[0m\n" , "%s\n" );
                exit( 1 );
            }

		    //consumer
		    ex_parte_consumer( kc );
	     }
	     else if( kc->mode == 'L' )
	     {
            if(  ( kc->topic_str == NULL ) || ( kc->brokers == NULL ) )
            {
                _L( "\033[0;31merror in metadata mode: topic and brokers must be specified.....\n\033[0m" , "%s\n" );
                stream_out_usage( kc->argv[0] );
                exit( 1 );
            }

            //metadata
            ex_parte_metadata( kc );
         }
         else if( kc->mode == 'M' )
	     {
         }
	     else
	     {
		    fprintf( stderr, "unrecognized mode...\n" );
		    exit( 1 );
	     }

         //free optarg copiesl neccessary since optarg and argv strings are mutabel
         if( kc->topic_str != NULL ) { free( kc->topic_str );  }
         if( kc->brokers! = NULL ) { free( kc->brokers );  }
         if( kc->group_id != NULL ) { free( kc->group_id );  }
         //free cli map
         cci_cli_dictionary_free( cdt  );


}

//------------------------------------------------------------------------
void cci_release_context( kafka_context_ptr kc  , int wait )
{
    assert( kc );

    _L( "terminating kafka library context..." , "%s\n" );

    //destroy topic
    rd_kafka_topic_destroy( kc->topic_ptr );
    //destroy handle
    rd_kafka_destroy( kc->kafka_ptr );


	//if produce or consume , let background threads
    //terminate cleanly
    if( wait ) { rd_kafka_wait_destroyed( 2000 ); }
}

//-------------------------------------------------------------------------
void cci_kf_logger ( const rd_kafka_t* ptr_handle ,
                     int level ,
           	         const char* fac ,
                     const char* buf )
{
	struct timeval tv;
	gettimeofday( &tv, NULL );

    fprintf( stderr ,
             "\033[22;32m%u.%03u RDKAFKA-\033[0m%i-%s: %s: %s\n" ,
		     (int) tv.tv_sec ,
             (int) ( tv.tv_usec / 1000 ) ,
		     level ,
             fac ,
             rd_kafka_name( ptr_handle ) ,
             buf );

}

//------------------------------------------------------------------------
void cci_kf_consumer_preamble( kafka_context_ptr kc )
{
         //init
        assert( kc  );

        char tmp[16];
        char errstr[512];

        _L( "consuming....." , "%s\n" );
        kc->conf_ptr = rd_kafka_conf_new();
        kc->conf_topic_ptr = rd_kafka_topic_conf_new();


        if( kc->debug_flags )
        {
            _L( "setting debug level....." , "%s\n" );
           debug_set( kc->conf_ptr , kc->debug_flags );
        }
        //set logger
        rd_kafka_conf_set_log_cb( kc->conf_ptr , kc->cci_logger );

        //quick termination
        snprintf(tmp, sizeof(tmp), "%i", SIGIO);
        rd_kafka_conf_set( kc->conf_ptr ,
                           "internal.termination.signal" ,
                           tmp ,
                           NULL ,
                           0 );
        _L( "setting configuration......." , "%s\n" );
        if( !kc->group_id ){ kc->group_id = "cci-group"; }
        if ( rd_kafka_conf_set( kc->conf_ptr ,
                                "group.id",
                                kc->group_id,
                                errstr ,
                                sizeof( errstr ) ) !=
                                RD_KAFKA_CONF_OK)
        {
                _L( "" , "%s" );
                fprintf( stderr, "%% %s\n", errstr );

                exit(1);
        }
        _L( "consumer groups configured...." , "%s\n" );

        //use broker based offset storage
        if ( rd_kafka_topic_conf_set( kc->conf_topic_ptr ,
                                      "offset.store.method" ,
                                      "broker" ,
                                       errstr ,
                                       sizeof( errstr ) ) !=
                                       RD_KAFKA_CONF_OK)
        {
                   _L( "" , "%s" );
                  fprintf( stderr, "%% %s\n", errstr );

                  exit(1);

        }
        _L( "configured offset storage...." , "%s\n" );

        //set default topic config for pattern-matched topics
        rd_kafka_conf_set_default_topic_conf( kc->conf_ptr , kc->conf_topic_ptr );

        //callback called on partition assignment changes
        rd_kafka_conf_set_rebalance_cb( kc->conf_ptr , kc->cci_partition_rebalance );
        _L( "set rebalancing context......." , "%s\n" );

        //consumer
        if ( !( kc->kafka_ptr = rd_kafka_new( RD_KAFKA_CONSUMER ,
                                              kc->conf_ptr ,
                                              errstr ,
                                              sizeof( errstr ) ) ) )
        {
               _L( "could not create consumer context...." , "%s\n" );
               _L( "" , "%s" );
               fprintf( stderr, "%% %s\n", errstr );

                exit( 1 );
        }
        context = kc;
        _L( "instantiated consumer context....." , "%s\n" );
        rd_kafka_set_log_level( kc->kafka_ptr , LOG_DEBUG );

}

//------------------------------------------------------------------------
void cci_kf_production_preamble( kafka_context_ptr kc )
{
        char tmp[16];
        char errstr[512];



        const char **arr;
        size_t cnt;
        int pass;

        kc->conf_ptr = rd_kafka_conf_new();

        if( kc->debug_flags )
        {
            _L( "setting debug level....." , "%s\n" );
           debug_set( kc->conf_ptr , kc->debug_flags );
        }

        //set logger
        rd_kafka_conf_set_log_cb( kc->conf_ptr , kc->cci_logger );
        //quick termination
        snprintf(tmp, sizeof(tmp), "%i", SIGIO);
        rd_kafka_conf_set( kc->conf_ptr ,
                           "internal.termination.signal" ,
                           tmp ,
                           NULL ,
                           0 );
        //topic config
        kc->conf_topic_ptr = rd_kafka_topic_conf_new();

        rd_kafka_topic_conf_set( kc->conf_topic_ptr ,
                                 "produce.offset.report" ,
                                 "true",  errstr ,
                                 sizeof( errstr ) );
        rd_kafka_conf_set_dr_msg_cb( kc->conf_ptr ,
                                     kc->cci_msg_delivered );

        _L( "emplaced report callback procs..." , "%s\n" );
        if( kc->dump_config ) { configuration_dump( kc ); }

        //create kafka handle
        if ( !( kc->kafka_ptr = rd_kafka_new( RD_KAFKA_PRODUCER ,
                                              kc->conf_ptr ,
                                              errstr ,
                                              sizeof(errstr) ) ) )
        {
            _L( "%% failed to create new producer..." , "%s\n" );

            exit(1);
        }
        _L( "created kafka library context...." , "%s\n" );

         rd_kafka_set_log_level( kc->kafka_ptr , LOG_DEBUG );

}



//------------------------------------------------------------------------
void cci_stop_signal( kafka_context_ptr kc )
{
    assert( kc );
    //assert( kc->kafka_ptr );


    //signal( SIGINT , stop );
    //signal( SIGTERM , stop );
    fprintf( stderr , "stop signal\n" );

}

//------------------------------------------------------------------------
void cci_usr1_signal( kafka_context_ptr kc )
{
    assert( kc );
    //assert( kc->kafka_ptr );

    context = kc;

    //signal( SIGINT , sig_usr1 );

}


//------------------------------------------------------------------------
void stream_out_usage( const char* binary )
{
     //stream , small subset of options
     fprintf( stderr ,
			"\033[22;32m%s\nusage:\n\t\t[-C|-P|-L|-D|-M] -t <topic> [-o <offset>] [-z hex message]\n" \
			"\t\t[-p <partition>] [-x dump-config] [-b <host1:port1,host2:port2,..>] [-g <group-id>]\n" \
			"\n" \
            "binary: %s\n" \
			"librdkafka version %s (0x%08x)\n" \
			"\n\033[0m" \
			" options:\n" \
			"  -C              consumer mode:\n" \
            "                  \twrites fetched messages to stdout\n" \
            "  -P              producer mode:\n" \
            "                  \tpost messages from stdout to stream...\n" \
            "  -L              metadata list mode\n" \
            "                  \tqueries broker for metadata information\n" \
            "  -D              describe consumer group\n" \
			"  -t <topics>     topics to fetch / produce\n" \
                        "\t\t  for balanced consumer groups use the 'topic1 topic2..'" \
                        " format\n" \
                        "\t\t  and for static assignment use " \
                        "'topic1:part1 topic1:part2 topic2:part1..'\n"\
            "  -o <offset>     offset to start queue consumption(0..n | OFFSET_END=-1  | OFFSET_BEGINNING=-2\n" \
            "  -p <num>        partition (random partitioner)\n" \
			"  -b <brokers>    broker address (localhost:9092)\n" \
            "  -g <groups>     consumer group ids\n" \
            "  -d <flags>      comma delimited string of flags. default is 'all'\n" \
                         "\t\t  :generic, broker, topic, metadata, producer, queue, msg\n" \
                         "\t\t  protocol, cgrp, security, fetch, all\n"\
            "  -x  dump configuration\n"
            "  -z  hex consumer messages=yes\n"
            "  -v  version\n"\
            "  -h  help\n%s" \
            "\n" \
			"\n" ,
            "----------------cci-kafka-plex------------chromatic universe 2018------ :\n"\
                "\n\t\t kafka demultiplexer and event manager for <cci mta stream ecosys> \n" ,
			binary ,
			rd_kafka_version_str() ,
            rd_kafka_version() ,
            "\033[22;32m\n--------------------------------------------------------------------------------------\n\n" \
            "binary: cci-stream-mta\n" \
            "version: 0.82\033[0m\n\n" \
            " options:\n" \
            "  -M                mta transfer mode:\n" \
            "                    \tmessage transfer agent rpc\n" \
        	"  -e <topics>       same as -t except exclusively mta managed topics\n" \
            "\n\033[22;32m\n--------------------------------------------------------------------------------------\033[0m\n\n" \

          );
}

//------------------------------------------------------------------------
void stream_out_partition_list ( FILE *fp ,
                                 int is_assigned ,
                                 const rd_kafka_topic_partition_list_t *partitions)
{

        int i;
        for ( i = 0 ; i < partitions->cnt ; i++ )
        {
                fprintf(stderr, "%s %s [%"PRId32"]",
                        i > 0 ? ",":"",
                        partitions->elems[i].topic,
                        partitions->elems[i].partition);

            if (is_assigned)
            {
                            context->wait_eof++;
            }
            else
            {
                            if ( context->exit_eof && --context->wait_eof == 0)
                                    context->is_running = 0;
            }
        }

        fprintf( stderr, "\n" );

}


//------------------------------------------------------------------------
void ex_parte_producer( kafka_context_ptr kc  )
{
    assert( kc  );

    int max_buf_len = 2048;
   	char buf[max_buf_len];
	int sendcnt = 0;

    _L( "starting production......" , "%s\n" );

    //init
    assert( kc );

    kc->cci_production_preamble( kc );

    metadata_set( kc );
    _L( "broker and topic metadata configured...." , "%s\n" );

    kc->is_running = 1;
    while ( kc->is_running && fgets( buf ,
                                     sizeof( buf ) ,
                                     stdin ) )
    {

		  	  size_t len = strlen( buf );
              if( len > max_buf_len ) { break; }
			  if( buf[len-1] == '\n' ) { buf[--len] = '\0'; }

              //send produce message
			  if( rd_kafka_produce( kc->topic_ptr ,
                                    kc->partition,
					                RD_KAFKA_MSG_F_COPY ,
					                //payload and len
            					    buf ,
                                    len ,
					                //optional key and its len
					                NULL ,
                                    0 ,
					                //message opaque, provided in
					                //delivery report callback as
					                //msg_opaque
					                NULL ) == -1 )
              {
				fprintf( stderr ,
					     "%% Failed to produce to topic %s "
				       	 "partition %i: %s\n",
					     rd_kafka_topic_name( kc->topic_ptr ) ,
                         kc->partition ,
					     rd_kafka_err2str( rd_kafka_last_error() ) );

				         //poll to handle delivery reports
 				         rd_kafka_poll( kc->kafka_ptr  , 0 );

                         continue;
			 }

             fprintf( stderr ,
                      "%% sent %zd bytes to topic " \
				  	  "%s partition %i\n",
				      len ,
                      rd_kafka_topic_name( kc->topic_ptr ) ,
                      kc->partition );
			 sendcnt++;
			 //poll to handle delivery reports
			 rd_kafka_poll( kc->kafka_ptr , 0 );

    }

    //wait for messages to be delivered
    while( kc->is_running && rd_kafka_outq_len( kc->kafka_ptr ) > 0 )
    { rd_kafka_poll( kc->kafka_ptr , 100 ); }

    //destroy topic
    if( kc->topic_ptr )
    {
        fclose( stdin );
        rd_kafka_topic_destroy( kc->topic_ptr );
        kc->topic_ptr = NULL;
    }
    //destroy the handle
    if( kc->kafka_ptr )
    {
        rd_kafka_destroy( kc->kafka_ptr );
        kc->kafka_ptr = NULL;
    }
    _L( "topics and context deleted...."  , "%s\n" );


}

//------------------------------------------------------------------------
void ex_parte_consumer(  kafka_context_ptr kc )
{
       //init
        assert( kc  );

        char errstr[512];
        int wait_eof = 0;
        int err;

        //preamble
        kc->cci_consumer_preamble( kc );
        assert( kc );

        //set metadata
        if ( rd_kafka_brokers_add( kc->kafka_ptr , kc->brokers ) == 0 )
        {
                    _L( "could not instantiate brokers...." , "%s\n" );
                    _L( "" , "%s" );
                    fprintf( stderr, "%%\%s\n" , errstr );

                    exit( 1 );
        }
        _L( "configured brokers...." , "%s\n" );

        //group description
        _L( "" , "%s" );
         describe_groups( kc->kafka_ptr , kc->group_id );

        //redirect polling
        rd_kafka_poll_set_consumer( kc->kafka_ptr );

        kc->partitions_ptr = rd_kafka_topic_partition_list_new( 10 );
        _L( "servicing topic partition distribution...." , "%s\n" );

        int is_subscription = process_partition_list( &kc->partitions_ptr  ,
                                                      kc->topic_str ,
                                                      &wait_eof ,
                                                      kc->start_offset );

        //subscribe
        if ( is_subscription )
        {
                    _L( "" , "%s" );
                    fprintf( stderr, "%% subscribing to %d topics....\n",
                            kc->partitions_ptr->cnt );

                    if ( ( err = rd_kafka_subscribe( kc->kafka_ptr , kc->partitions_ptr ) ) )
                    {
                            _L( "" , "%s" );
                            fprintf( stderr,
                                    "%% failed to start consuming topics: %s\n",
                                    rd_kafka_err2str( err ) );
                            exit( 1 );
                    }
                    _L( "subscribed...." , "%s\n" );
        }
        else
        {
                    //assign partitions
                    _L( "" , "%s" );
                    fprintf( stderr , "%% assigning %d partitions\n" ,
                                       kc->partitions_ptr->cnt );

                    if ( ( err = rd_kafka_assign( kc->kafka_ptr , kc->partitions_ptr ) ) )
                    {
                            _L( "" , "%s" );
                            fprintf( stderr,
                                    "%% failed to assign partitions: %s\n",
                                    rd_kafka_err2str( err ) );
                    }
        }

        //consume messages
        kc->is_running = 1;
        while ( kc->is_running )
        {
                    message_k_ptr message_ptr;

                    message_ptr = rd_kafka_consumer_poll( kc->kafka_ptr , 1000 );
                    if ( message_ptr )
                    {
                            kc->cci_msg_consume( kc , message_ptr , NULL );

                            rd_kafka_message_destroy( message_ptr );
                    }
        }

        //close
        err = rd_kafka_consumer_close( kc->kafka_ptr );
        if ( err )
        {
              _L( "" , "%s\n" );
              fprintf (stderr ,
                       "%% failed to close consumer: %s\n",
                                rd_kafka_err2str( err ) );
        }
        else
        {
              _L( "" , "%s");
              fprintf( stderr, "%% consumer closed..............\n");
              //destory partitions
              rd_kafka_topic_partition_list_destroy( kc->partitions_ptr );
              //destroy handle
              rd_kafka_destroy(  kc->kafka_ptr );
              int run = 5;
              while ( run-- > 0 && rd_kafka_wait_destroyed( 1000 ) == -1 )
              {
                _L( "waiting for librdkafka to decommission...." ,  "%s\n" );
              }
              if ( run <= 0 ) { rd_kafka_dump( stderr , kc->kafka_ptr ); }
        }

}

//-----------------------------------------------------------------------
void ex_parte_metadata( kafka_context_ptr kc )
{

         _L( "...metadata...." , "%s\n" );

        kc->cci_production_preamble( kc );
        rd_kafka_resp_err_t err = RD_KAFKA_RESP_ERR_NO_ERROR;
        metadata_set_ex( kc );
        _L( "broker and topic metadata configured...." , "%s\n" );

         //Fetch metadata
        _L( "...fetching metadata...." , "%s\n" );

        const struct rd_kafka_metadata *metadata;
        err = rd_kafka_metadata( kc->kafka_ptr ,
                                 kc->topic_ptr ? 0 : 1 ,
                                 kc->topic_ptr ,
                                 &metadata ,
                                 5000 );
        if  (err != RD_KAFKA_RESP_ERR_NO_ERROR )
        { _L( rd_kafka_err2str( err ) , "...fetch metadata failed d%s/n" ); }
        else { kc->cci_topic_metadata( kc->topic_str , metadata ); }

        rd_kafka_metadata_destroy( metadata );

        //destroy topic and ttopic config
        if( kc->topic_ptr )
        {
            fclose( stdin );
            rd_kafka_topic_destroy( kc->topic_ptr );
            kc->topic_ptr = NULL;
        }
        //destroy the handle
        if( kc->kafka_ptr )
        {
            rd_kafka_destroy( kc->kafka_ptr );
            kc->kafka_ptr = NULL;
        }

        _L( "topics and context deleted...."  , "%s\n" );
        _L( "...end fetch metadata metadata...." , "%s\n" );


}

//------------------------------------------------------------------------
void make_kafka_handle( kafka_context_ptr kc   )
{
        char errstr[512];
        char tmp[16];

        //init conf
        _L( "new configuration..." , "%s\n" );
        kc->conf_ptr = rd_kafka_conf_new();
        assert( kc->conf_ptr );
        //quick termination
        snprintf( tmp , sizeof( tmp ) , "%i" , SIGIO );
        rd_kafka_conf_set( kc->conf_ptr ,
                            "internal.termination.signal" ,
                            tmp ,
                            NULL ,
                            0 );
        //debug
        if( kc->debug_flags )
        {
            _L( "setting debug flags...." , "%s\n" );
            if ( rd_kafka_conf_set( kc->conf_ptr ,
                                   "debug" ,
                                    kc->debug_flags ,
                                    errstr ,
                                    sizeof( errstr ))  !=
                                    RD_KAFKA_CONF_OK)
            {
                fprintf( stderr ,
                        "%%debug configuration failed: %s: %s\n",
                         errstr ,
                         "all" );
                exit( 1) ;
            }
        }
        //client consumer group
        _L( "setting consumer groups...." , "%s\n" );
        if( !kc->group_id )  { kc->group_id = "cci-group"; }
        if ( rd_kafka_conf_set( kc->conf_ptr ,
                                "group.id" ,
                                kc->group_id ,
                                errstr ,
                                sizeof( errstr ) ) !=
                                RD_KAFKA_CONF_OK )
        {
                            fprintf( stderr ,
                                     "%% %s\n" ,
                                     errstr );
                            exit ( 1 );
        }

        //topic conf
        _L( "topic oconfiguration...." , "%s\n" );
        kc->conf_topic_ptr  = rd_kafka_topic_conf_new();
        assert( kc->conf_topic_ptr );

        //broker offset storag
        _L( "setting broker offset storage...." , "%s\n" );
        if( rd_kafka_topic_conf_set( kc->conf_topic_ptr ,
                                     "offset.store.method",
                                     "broker",
                                     errstr ,
                                     sizeof( errstr ) ) !=
                                     RD_KAFKA_CONF_OK )
        {
                            fprintf( stderr ,
                                    "%% %s\n" ,
                                    errstr );
                            exit( 1 );
        }

        //default topic config for pattern-matched topics
        _L( "setting default topic...." , "%s\n" );
        rd_kafka_conf_set_default_topic_conf( kc->conf_ptr , kc->conf_topic_ptr );
        _L( "rebalance callbacke set...." , "%s\n" );
        //rebalance callback call for partition reassignment
        rd_kafka_conf_set_rebalance_cb( kc->conf_ptr , kc->cci_partition_rebalance );

        //file scope pointer
        context = kc;

        //create kafka handle
        _L( "creating library context...." , "%s\n" );
        if( !( kc->kafka_ptr = rd_kafka_new( kc->mode == 'C' ? RD_KAFKA_CONSUMER
                                              : RD_KAFKA_PRODUCER ,
                                             kc->conf_ptr ,
                                             errstr ,
                                             sizeof( errstr ) ) ) )
        {
                fprintf( stderr ,
                         "%% Failed to create new context: %s\n",
                          errstr );

                exit( 1 );
        }

        _L( "redirecting log stream...." , "%s\n" );
        //redirect rd_kafka_poll() to consumer_poll()
        rd_kafka_poll_set_consumer( kc->kafka_ptr );

        //partition list
        _L( "setting up partition list...." , "%s\n" );
        kc->partitions_ptr = rd_kafka_topic_partition_list_new( 10 );



}

//------------------------------------------------------------------------
void make_kafka_logger( kafka_context_ptr kc  )
{
    assert( kc );
    assert( kc->kafka_ptr );

    //set logger
    rd_kafka_conf_set_log_cb( kc->conf_ptr , kc->cci_logger );

    rd_kafka_set_log_level( kc->kafka_ptr , LOG_DEBUG );

}

//------------------------------------------------------------------------
void metadata_set( kafka_context_ptr kc )
{
        assert( kc );
        assert( kc->kafka_ptr );
        assert( kc->brokers );

        //add brokers
        if( rd_kafka_brokers_add( kc->kafka_ptr ,
                                  kc->brokers ) == 0 )
        {
              _L( "%% No valid brokers specified....." , "%s\n" );
              exit( 1 );
        }

        //create topic
        kc->topic_ptr = rd_kafka_topic_new( kc->kafka_ptr ,
                                            kc->topic_str ,
                                            kc->conf_topic_ptr );
        if( !kc->topic_ptr )
        {
            _L( "invalid topic specified....." , "%s" );
            exit( 1 );
        }

}

//------------------------------------------------------------------------
void metadata_set_ex( kafka_context_ptr kc )
{
        assert( kc );
        assert( kc->kafka_ptr );
        assert( kc->brokers );

        //add brokers
        if( rd_kafka_brokers_add( kc->kafka_ptr ,
                                  kc->brokers ) == 0 )
        {
              _L( "%% No valid brokers specified....." , "%s\n" );
              exit( 1 );
        }

        if( kc->topic_str )
        {
            //create topic
            kc->topic_ptr = rd_kafka_topic_new( kc->kafka_ptr ,
                                                kc->topic_str ,
                                                kc->conf_topic_ptr );
            if( !kc->topic_ptr )
            {
                _L( "invalid topic specified....." , "%s" );
                exit( 1 );
            }
        }
        else
        { kc->topic_ptr = NULL; }

}


//------------------------------------------------------------------------
void debug_set( conf_k_ptr ptr , const char* contexts )
{
    char errstr[512];

    if ( rd_kafka_conf_set( ptr ,
                            "debug",
                            contexts ,
					        errstr,
                            sizeof( errstr ) ) !=
			                RD_KAFKA_CONF_OK )
    {
			_L(	"%% debug configuration failed...." , "%s\n" );

			exit( 1 );
    }
}

//------------------------------------------------------------------------
int process_partition_list( partition_list_ptr* partitions  ,
                                                const gchar*  topics ,
                                                int* wait ,
                                                int offset )
{
    // form 1 => <topic1 topic2 etc.> balanced partition
    // form 2 => <topic1:0 topic2:1 etc> statically assigned partition

    int is_subscription = 1;
    gchar** atom = NULL;
    gchar*  topic = NULL;
    int i = 0;

    //comma delmited list...
    gchar** vector = g_strsplit( topics , " " , 0 );
    if( vector )
    {
        for( i = 0; vector[i]; i++ )
        {
            int32_t partition = -1;
            //if colon delimited pair....
            gchar* find = g_strrstr( vector[i] ,  ":"  );
            if( find )
            {
                //static partition assignment
                is_subscription = 0;
                atom = g_strsplit( vector[i] , ":" , 0 );
                //partition number
                partition = atoi( atom[1] );
                topic = atom[0];
                wait++;
            }else{ topic = vector[i]; }
            //add to partition assignment list
            rd_kafka_topic_partition_list_add( *partitions , topic , partition )->offset = RD_KAFKA_OFFSET_END;
            g_strfreev( atom );
            atom = NULL;
        }

    }
    g_strfreev( vector );

    _L( "" , "%s" );
    is_subscription ? fprintf( stderr ,
                               "configured partitions for %d balanced topic(s)..\n" ,
                               i ) :
                      fprintf( stderr ,
                               "configured patoartitions for %d static topic(s)..\n" ,
                               i );


    return is_subscription;
}


//------------------------------------------------------------------------
void sig_usr1 ( int sig )
{
	//rd_kafka_dump( stdout , context->kafka_ptr );
}


//------------------------------------------------------------------------
void _L( const char* buf , const char* format )
{
        time_t timer;
        char buffer[26];
        struct tm* tm_info;

        time( &timer );
        tm_info = localtime( &timer );

        strftime( buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info );

        struct timeval tv;
        gettimeofday( &tv, NULL );
        fprintf( stderr ,
                 "\033[22;34m%u.%03u CCI-KAFKA-PLEX %s:\033[0m" ,
                 (int) tv.tv_sec ,
                 (int) ( tv.tv_usec / 1000 ) ,
                 buffer );
        fprintf( stderr ,
                 format ,
                 buf  );

}

//-------------------------------------------------------------------------
int describe_groups (rd_kafka_t *rk, const char *group)
{
        rd_kafka_resp_err_t err;
        const struct rd_kafka_group_list *grplist;
        int i;

        err = rd_kafka_list_groups(rk, group, &grplist, 10000);

        if (err) {
                fprintf(stderr, "%% Failed to acquire group list: %s\n",
                        rd_kafka_err2str(err));
                return -1;
        }

        for (i = 0 ; i < grplist->group_cnt ; i++) {
                const struct rd_kafka_group_info *gi = &grplist->groups[i];
                int j;

                printf("Group \"%s\" in state %s on broker %d (%s:%d)\n",
                       gi->group, gi->state,
                       gi->broker.id, gi->broker.host, gi->broker.port);
                if (gi->err)
                        printf(" Error: %s\n", rd_kafka_err2str(gi->err));
                printf(" Protocol type \"%s\", protocol \"%s\", "
                       "with %d member(s):\n",
                       gi->protocol_type, gi->protocol, gi->member_cnt);

                for (j = 0 ; j < gi->member_cnt ; j++) {
                        const struct rd_kafka_group_member_info *mi;
                        mi = &gi->members[j];

                        printf("  \"%s\", client id \"%s\" on host %s\n",
                               mi->member_id, mi->client_id, mi->client_host);
                        printf("    metadata: %d bytes\n",
                               mi->member_metadata_size);
                        printf("    assignment: %d bytes\n",
                               mi->member_assignment_size);
                }
                printf("\n");
        }

        if (group && !grplist->group_cnt)
                fprintf(stderr, "%% No matching group (%s)\n", group);

        rd_kafka_group_list_destroy(grplist);

        return 0;
}

//-------------------------------------------------------------------------
void configuration_dump( kafka_context_ptr kc )
{
        const char **arr;
		size_t cnt;
		int pass;

        _L( "dumping configuration...." , "%s\n" );
        assert( kc->conf_ptr );
		for ( pass = 0 ; pass < 2 ; pass++ )
        {
			if ( pass ==  0 )
            {
				arr = rd_kafka_conf_dump( kc->conf_ptr , &cnt );
                _L( "" , "%s" );
				printf( "*****  global config *****\n" );
			}
            else
            {
                   _L( "" , "%s" );
                   printf( "****** topic config ******\n" );
                   arr = rd_kafka_topic_conf_dump( kc->conf_topic_ptr ,
							                    &cnt );
			}

			for ( int i = 0 ; i < (int) cnt; i += 2 )
            {
                _L( "" , "%s" );
				printf(" %s = %s\n" ,
				       arr[i] , arr[i+1] );
            }


			rd_kafka_conf_dump_free( arr , cnt );
		}


}







