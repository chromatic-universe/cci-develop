// cci_kafka_q.h       william k. johnson 2016

#pragma once

//c runtime
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
//cci
#include "cci_mini_kafka.h"
#include <cci_daemon.h>


struct work
{
    struct work *next;
    struct nn_msghdr request;
    uint64_t expire;
    void *control;
    char* payload;
};


//--------------------------------------------------------------------------------
extern uint64_t milliseconds (void);
//--------------------------------------------------------------------------------
extern int kafka_server_q( const char* url , kafka_context_ptr kc );
//--------------------------------------------------------------------------------
extern int kafka_client_q ( const char* url , const char* packet , int* rfd , int len  );
//------------------------------------------------------------------------
extern int dispatch_first_atom( const char* url , const char* packet , int len );
//------------------------------------------------------------------------
extern void dispatch_atom( const char* url , const char* packet , int len , int* handle );
//------------------------------------------------------------------------
extern void dispatch_last_atom( const char* url , const char* packet , int len , int* handle );
