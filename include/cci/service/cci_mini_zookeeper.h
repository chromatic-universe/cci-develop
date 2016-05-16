//cci_mini_zookeeper.h william k. johnson 2016
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma once

#include "cci/cci.h"
#include <errno.h>

#include <gen-c_glib/curator_service.h>
#include <gen-c_glib/event_service.h>

typedef struct curator_context
{
    //commandline
    int argc;
    int argv;
    ///services
    //ctor


}curator_context;
typedef curator_context* curator_context_ptr;
