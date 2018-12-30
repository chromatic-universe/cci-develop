//cci_mini_kafka.h william k. johnson 2015
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma once


#include <glib.h>
#include <gnu/libc-version.h>

//inclusion of asprintf
#define _GNU_SOURCE



//c runtime
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <paths.h>
#include <dirent.h>
#include <sys/syscall.h>

//contrib
#include <librdkafka/rdkafka.h>
//cci
#include <cci_cli_dictionary.h>


//types
typedef void* void_ptr;


static  enum {
	OUTPUT_HEXDUMP,
	OUTPUT_RAW,
} output = OUTPUT_RAW;

//types
typedef FILE* file_ptr;
typedef rd_kafka_message_t*                     message_ptr_k;
typedef struct rd_kafka_metadata*               metadata_ptr_k;
typedef struct rd_kafka_metadata_topic*         metadata_topic_ptr_k;
typedef struct rd_kafka_metadata_partition*     metadata_partition_ptr_k;
typedef rd_kafka_topic_t*                       topic_ptr_k;
typedef rd_kafka_conf_t*                        conf_k_ptr;
typedef rd_kafka_topic_conf_t*                  topic_conf_k_ptr;
typedef rd_kafka_t*                             handle_k_ptr;
typedef rd_kafka_message_t*                     message_k_ptr;
typedef rd_kafka_topic_partition_list_t*        partition_list_ptr;




//structures
typedef struct kafka_context
{
            //library context
            handle_k_ptr       kafka_ptr;
            ///interface references
            conf_k_ptr         conf_ptr;
            topic_conf_k_ptr   conf_topic_ptr;
            topic_ptr_k        topic_ptr;
            ///attributes
            //brokers
            const char*        brokers;
            //topic string
            const char*        topic_str;
            //group
            const char*        group_id;
            //partition list
            partition_list_ptr partitions_ptr;
            //mode
            char               mode;
            //partition
            int                partition;
            //debug flags
            const char*        debug_flags;
            //dumbp config
            int                dump_config;
            //hex message output
            int                hex_out;
            //running
            int                is_running;
            //exit consuming on nom more messages
            int                exit_eof;
            //partitions waiting for eof
            int                wait_eof;
            //start offset for consumption
            int64_t            start_offset;
            //group
            const char*        group;
            //commmand line
            int                argc;
            char**             argv;
            ///services
            //ctors
            void               ( *cci_production_preamble ) ( struct kafka_context* kc );
            void               ( *cci_consumer_preamble ) ( struct kafka_context* kc );
            //main
            void               ( *cci_mini_run )( struct kafka_context* kc );
            //dtor
            void               ( *cci_release_context ) (  struct kafka_context* kc  , int wait );
            //signal stop
            void               ( *cci_stop_signal ) ( struct kafka_context* kc );
            //signal usr1
            void               ( *cci_usr1_signal ) ( struct kafka_context* kc );
            //logging
            void               ( *cci_logger ) ( const rd_kafka_t* ptr_handle ,
                                                 int level ,
                                                 const char *fac ,
                                                 const char *buf );
            //hex dump
            void               ( *cci_hex_dump  ) ( file_ptr fp ,
                                                    const char* name ,
                                                    const void_ptr ptr ,
                                                    size_t len );
            //topic metadata
            void               ( *cci_topic_metadata ) ( const char *topic ,
                                                         const struct rd_kafka_metadata *metadata  );
            //consume
            void               ( *cci_msg_consume ) ( struct kafka_context* kc ,
                                                      message_ptr_k rkmessage ,
                                                      void_ptr opaque );
            //producer callback
            void               ( *cci_msg_delivered ) ( rd_kafka_t *rk ,
                                                        const rd_kafka_message_t* rkmessage ,
                                                        void_ptr opaque );
            //rebalance callback
            void               ( *cci_partition_rebalance )( rd_kafka_t *rk ,
                                                             rd_kafka_resp_err_t err ,
                                                             rd_kafka_topic_partition_list_t *partitions ,
                                                             void *opaque ) ;



} kafka_context;
typedef kafka_context* kafka_context_ptr;

//callbacks
//
//optional logging callback
//deprecated librdkafka 0.9
extern void cci_kf_logger ( const rd_kafka_t* ptr_handle ,
                            int level ,
           	                const char *fac ,
                            const char *buf );
//------------------------------------------------------------------------
//message delivery callback
extern void cci_kf_msg_delivered( rd_kafka_t *rk ,
                                  const rd_kafka_message_t* rkmessage ,
                                  void_ptr opaque );
//------------------------------------------------------------------------
//services
//message consume
extern void cci_kf_msg_consume( kafka_context_ptr kc ,
                                message_ptr_k rkmessage ,
                                void_ptr opaque );
//------------------------------------------------------------------------
//production preamble
extern void cci_kf_production_preamble( kafka_context_ptr kc );
//------------------------------------------------------------------------
//consumer preamble
extern void cci_kf_consumer_preamble( kafka_context_ptr kc );
//------------------------------------------------------------------------
//hex dump
extern void cci_kf_hex_dump( file_ptr fp, const char *name, const void_ptr ptr , size_t len );
//------------------------------------------------------------------------
//metadata print
extern void cci_kf_metadata_print (  const char *topic ,
                                     const struct rd_kafka_metadata *metadata );
//------------------------------------------------------------------------
//mini run
extern void cci_kf_mini_run( kafka_context_ptr kc );
//-----------------------------------------------------------------yy-------
//release context
extern void cci_release_context(  kafka_context* kc  , int wait );
//------------------------------------------------------------------------
//stop signal
extern void cci_stop_signal( kafka_context_ptr );
//------------------------------------------------------------------------
//usr1 signal
extern void cci_usr1_signal( kafka_context_ptr );
//------------------------------------------------------------------------
extern void cci_kf_rebalance_cb (  rd_kafka_t *rk,
                                   rd_kafka_resp_err_t err ,
                                   rd_kafka_topic_partition_list_t *partitions ,
                                   void *opaque );

