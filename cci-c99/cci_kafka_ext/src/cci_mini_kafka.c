//cci_mini_kafka.c william k. johnson 2015

#include <cci_mini_kafka.h>

static kafka_context_ptr  context = NULL;

int quiet = 0;
int run = 1;
int exit_eof = 0;

static  kafka_context* gkc;
static void deactivate( int sig )
{
    assert( gkc );
    //kill fgetc
    fclose( stdin );
    //halt kafka
    gkc->is_running = 0;
}

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
//rebalance stream
void stream_out_partition_list ( FILE *fp ,
                                 int is_assigned ,
                                 const rd_kafka_topic_partition_list_t *partitions);
//------------------------------------------------------------------------
static void make_kafka_handle( kafka_context_ptr kc  );
//------------------------------------------------------------------------
static void make_kafka_logger( kafka_context_ptr kc );
//------------------------------------------------------------------------
static void metadata_set( kafka_context_ptr kc );
//------------------------------------------------------------------------
static void debug_set( conf_k_ptr ptr , const char* contexts );
//------------------------------------------------------------------------
static void _L( const char* buf , const char* format );
//------------------------------------------------------------------------
static int process_partition_list( partition_list_ptr* partitions  ,
                                                const char*  topics ,
                                                int* wait );



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

   if (rkmessage->err) {
		if (rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) {
            _L( "" , "%s" );
			fprintf(stderr,
				"consumer reached end of %s [%"PRId32"] "
			       "message queue at offset %"PRId64"\n",
			       rd_kafka_topic_name(rkmessage->rkt),
			       rkmessage->partition, rkmessage->offset);

			if ( kc->exit_eof && --kc->wait_eof == 0) {
                                fprintf(stderr,
                                        "%% All partition(s) reached EOF: "
                                        "exiting\n");
				kc->is_running = 0;
                        }

			return;
		}

                if (rkmessage->rkt)
                        fprintf(stderr, "%% Consume error for "
                                "topic \"%s\" [%"PRId32"] "
                                "offset %"PRId64": %s\n",
                                rd_kafka_topic_name(rkmessage->rkt),
                                rkmessage->partition,
                                rkmessage->offset,
                                rd_kafka_message_errstr(rkmessage));
                else
                        fprintf(stderr, "%% Consumer error: %s: %s\n",
                                rd_kafka_err2str(rkmessage->err),
                                rd_kafka_message_errstr(rkmessage));

                if (rkmessage->err == RD_KAFKA_RESP_ERR__UNKNOWN_PARTITION ||
                    rkmessage->err == RD_KAFKA_RESP_ERR__UNKNOWN_TOPIC)
                        kc->is_running = 0;
		return;
	}

		fprintf(stdout, "%% Message (topic %s [%"PRId32"], "
                        "offset %"PRId64", %zd bytes):\n",
                        rd_kafka_topic_name(rkmessage->rkt),
                        rkmessage->partition,
			rkmessage->offset, rkmessage->len);

	if (rkmessage->key_len) {
		if (output == OUTPUT_HEXDUMP)
			cci_kf_hex_dump(stdout, "Message Key",
				rkmessage->key, rkmessage->key_len);
		else
			printf("Key: %.*s\n",
			       (int)rkmessage->key_len, (char *)rkmessage->key);
	}
  	if (output == OUTPUT_HEXDUMP)
		cci_kf_hex_dump(stdout, "Message Payload",
			rkmessage->payload, rkmessage->len);
	else
		printf("%.*s\n",
		       (int)rkmessage->len, (char *)rkmessage->payload);

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

     printf( "\033[22;34mmetadata for %s (from broker %"PRId32": %s):\n" ,
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
                printf( "  topic \"%s\" with %i partitions:" ,
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
      printf( "\033[0m" );
}

//------------------------------------------------------------------------
void cci_kf_mini_run( kafka_context_ptr kc )
{

	 int opt;


     quiet = !isatty( STDIN_FILENO );

     while ( ( opt = getopt( kc->argc ,
                             kc->argv ,
                             "PCLDt:d:p:b:o:g:xevh" ) ) != -1 )
     {
         switch( opt )
         {

            //modes
            //producer
            case 'P' :
            //consumer
		    case 'C' :
            //group description
            case 'D' :
            //metadata list mode
            case 'L' :
                if( kc->mode )
                {
                    _L( "mode has already been set..." , "%s\n" );
                    exit( 1 );
                }
                kc->mode = opt;
                break;

            //consumption offset
		    case 'e':
			    kc->exit_eof = 1;
			    break;
            //topic
            case 't' :
			    kc->topic_str = optarg;
			    break;
            //partition
	        case 'p':
			    kc->partition = atoi( optarg );
			    break;
            //brokers
		    case 'b' :
			    kc->brokers = optarg;
			    break;
            //group
            case 'g' :
                kc->group_id = optarg;
                break;
            //group
            case 'd' :
                kc->debug_flags = optarg;
                break;
            //dump configuration
            case 'x' :
                kc->dump_config = 1;
                break;
            //consumption offset
		    case 'o':
			    kc->start_offset = atoi( optarg );
			    break;
            case 'v':
                fprintf( stderr , "\033[22;32mcci_mini_kafka_run version 0.8 william k. johnson 2016\n\033[0m" );
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
         fprintf( stderr, "mode must be specified...\n" );
         exit( 1 );
     }
     if( kc->mode == 'P' )
     {
        ex_parte_producer( kc );
	 }
     else if( ( kc->mode == 'C' ) || ( kc->mode == 'D' ) )
     {
        //consumer
        ex_parte_consumer( kc );
     }
     else if( kc->mode == 'L' )
     {
     }
     else
     {
         fprintf( stderr, "unrecognized mode...\n" );
         exit( 1 );
     }


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
    signal( SIGINT , deactivate );
    signal( SIGTERM , deactivate );

    gkc = kc;

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

     metadata_set( kc );
    _L( "broker and topic metadata configured...." , "%s\n" );


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
			"\033[22;32m%s\nusage:\n\t\t-C|-P|-L|D -t <topic> [-o <offset>]\n" \
			"\t\t[-p <partition>] [-x dump-config] [-b <host1:port1,host2:port2,..>] [-g <group-id>]\n" \
			"\n" \
            "binary: %s\n" \
			"librdkafka version %s (0x%08x)\n" \
			"\n\033[0m" \
			" options:\n" \
			"  -C              consumer mode:\n" \
            "                  writes fetched messages to stdout\n" \
            "  -P              producer mode:\n" \
            "                  queries broker for metadata information\n" \
            "  -L              metadata list mode\n" \
            "                  queries broker for metadata information\n" \
            "  -D              describe consumer group\n" \
			"  -t <topics>     topics to fetch / produce\n" \
                        "\t\t  for balanced consumer groups use the 'topic1 topic2..'" \
                        " format\n" \
                        "\t\t  and for static assignment use " \
                        "'topic1:part1 topic1:part2 topic2:part1..'\n"\
            "  -o <offset>     offset to start queue consumption\n" \
            "  -p <num>        partition (random partitioner)\n" \
			"  -b <brokers>    broker address (localhost:9092)\n" \
            "  -g <groups>     consumer group ids\n" \
            "  -d <flags>      comma delimited string of flags. default is 'all'\n" \
                         "\t\t  :generic, broker, topic, metadata, producer, queue, msg\n" \
                         "\t\t  protocol, cgrp, security, fetch, all\n"\
            "  -x  dump configuration\n"
            "  -v  version\n"\
            "  -h  help\n\n" \
			"\n" \
			"\n" ,
            "synopsis :\n"\
                "\n\t\t mini utils for kafka server manip\n" ,
			binary ,
			rd_kafka_version_str() ,
            rd_kafka_version()
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
void ex_parte_atomic_production( kafka_context_ptr kc ,
                                 const char* packet ,
                                 int len )
{

        assert( kc  );

        int max_buf_len = 2048;

        _L( "..production atom......" , "%s\n" );

        // no-op
        if( len > max_buf_len ) { return; }

        //send produce message
         if( rd_kafka_produce( kc->topic_ptr ,
                                kc->partition,
                                RD_KAFKA_MSG_F_COPY ,
                                //payload and len
                                (void*) packet ,
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
                     rd_kafka_err2str( rd_kafka_errno2err( errno ) ) );
          }

          fprintf( stderr ,
                  "%% sent %zd bytes to topic " \
                  "%s partition %i\n",
                   len ,
                   rd_kafka_topic_name( kc->topic_ptr ) ,
                   kc->partition );
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

        cci_kf_production_preamble( kc );

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
                             rd_kafka_err2str( rd_kafka_errno2err( errno ) ) );

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

        cci_kf_consumer_preamble( kc );
        assert( kc->kafka_ptr );

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
                                                      &wait_eof );

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
        while ( kc->is_running ==  1 )
        {
                    message_k_ptr message_ptr;

                    message_ptr = rd_kafka_consumer_poll( kc->kafka_ptr , 1000 );
                    if ( message_ptr )
                    {
                            cci_kf_msg_consume( kc , message_ptr , NULL );

                            rd_kafka_message_destroy( message_ptr );
                    }
                    else {  continue; }
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
              rd_kafka_dump( stderr , kc->kafka_ptr );

              fprintf( stderr, "%% consumer closed..............\n");
              //destory partitions
              rd_kafka_topic_partition_list_destroy( kc->partitions_ptr );
              //destroy topic
              rd_kafka_topic_destroy( kc->topic_ptr );
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
void sig_usr1 ( int sig )
{
	//rd_kafka_dump( stdout , context->kafka_ptr );
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

                printf("Group \"%s\" in state %s on broker %d (%s:%hu)\n",
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
                //_L( "" , "%s" );
				//printf( "%%%%%% global config %%%%%%%\n" );
			}
            else
            {
                   _L( "" , "%s" );
                   printf( "%%%%%% topic config %%%%%%\n" );
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




