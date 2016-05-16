//cci_mini_trace.h  william k. johnson 2015
//
////portions shoplifted from :
//Freedom Embedded by Francesco Balducci is licensed under a Creative Commons Attribution-Share Alike 4.0 License.
//
//the strange dearth of tracing tools for c
//
#pragma once


#include <stdio.h>
#include <time.h>

typedef FILE* cci_trace_file_ptr;
extern  cci_trace_file_ptr ctfp;

//straight from da man
//
//finstrument-functions
//Generate instrumentation calls for entry and exit to functions. Just after function entry and just before function exit, the following profiling functions will be called with the address of the current function and its call site. […]
//
//              void __cyg_profile_func_enter (void *this_fn,
//                                             void *call_site);
//              void __cyg_profile_func_exit  (void *this_fn,
//                                             void *call_site);


//------------------------------------------------------------------------
void __attribute__ ( ( constructor ) ) trace_begin( void );
 //-----------------------------------------------------------------------
void __attribute__ ( ( destructor ) ) trace_end( void );
//------------------------------------------------------------------------
void __cyg_profile_func_enter ( void *func , void *caller );
//------------------------------------------------------------------------
void __cyg_profile_func_exit ( void *func ,  void *caller );

