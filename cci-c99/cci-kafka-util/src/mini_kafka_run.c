//mini_run_kafka.c   william k. johnson 2016

#include <cci_mini_kafka.h>

static  kafka_context* gkc;
static void deactivate( int sig )
{
    assert( gkc );
    //kill fgetc
    fclose( stdin );
    //halt kafka
    gkc->is_running = 0;
}


int main( int argc , char* argv[] )
{

    signal( SIGINT , deactivate );
    signal( SIGTERM , deactivate );

    kafka_context kc = {  ///attributes
                          //
                          //lib context
                          .kafka_ptr = NULL ,
                          //config
                          .conf_ptr = NULL ,
                          //topic config
                          .conf_topic_ptr = NULL ,
                          //topic string
                          .topic_str = NULL ,
                          //topic context
                          .topic_ptr = NULL ,
                          //default brokers
                          .brokers = NULL ,
                          //group id
                          .group_id = NULL ,
                          //partitions
                          .partitions_ptr = NULL ,
                          //random /partitioner
                          .partition = -1 , //RD_KAFKA_PARTITION_UA ,
                          //devug flags
                          .debug_flags = NULL ,
                          //dumb config
                          .dump_config = 0 ,
                          //hex message output
                          .hex_out = OUTPUT_RAW ,
                          //running
                          .is_running = 0 ,
                          //eof - false
                          .exit_eof = 0 ,
                          //partition wait eof
                          .wait_eof = 0 ,
                          //queue offset
                          .start_offset = RD_KAFKA_OFFSET_END ,
                          //default mode consumer
                          .mode = 0 ,
                          //command line
                          .argc = argc ,
                          .argv = argv ,
                          ///services
                          //
                          //run
                          .cci_mini_run = cci_kf_mini_run ,
                          //sub contexts
                          .cci_production_preamble = cci_kf_production_preamble ,
                          .cci_consumer_preamble = cci_kf_consumer_preamble ,
                          //release
                          .cci_release_context = cci_release_context ,
                          //signals
                          .cci_stop_signal = cci_stop_signal ,
                          .cci_usr1_signal = cci_usr1_signal ,
                          //logging
                          .cci_logger = cci_kf_logger ,
                          //hex
                          .cci_hex_dump = cci_kf_hex_dump ,
                          //topic metadata
                          .cci_topic_metadata =  cci_kf_metadata_print ,
                          //consume
                          .cci_msg_consume = cci_kf_msg_consume ,
                          //producer callback
                          .cci_msg_delivered = cci_kf_msg_delivered ,
                          //rebalance callback
                          .cci_partition_rebalance = cci_kf_rebalance_cb
                       };

    //kafka context for signals
    gkc = &kc;
    //run
    kc.cci_mini_run( &kc );

    return 0;
}

