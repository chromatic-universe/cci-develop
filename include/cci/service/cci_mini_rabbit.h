//cci_mini_rabbit.h  william k. johnson 2015
//rabbitmq walk-a-baby
#pragma once

//c runtime
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
//rabbitmq
#include <amqp.h>
#include <amqp_framing.h>
#include <amqp_tcp_socket.h>

//utils
//
//------------------------------------------------------------------------
void die( const char *fmt , ... );
//------------------------------------------------------------------------
extern void die_on_error( int x , char const *context );
//------------------------------------------------------------------------
extern void die_on_amqp_error( amqp_rpc_reply_t x , char const *context );
//------------------------------------------------------------------------
extern void amqp_dump( void const *buffer , size_t len );
//------------------------------------------------------------------------
extern uint64_t now_microseconds( void );
//------------------------------------------------------------------------
extern void microsleep( int usec );


