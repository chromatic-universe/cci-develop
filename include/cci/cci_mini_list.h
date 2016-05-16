//cci_mini_list.h william k. johnson 2015


#pragma once
//
//minimal no noise list implementation
//useful for macros and function pointer
//structures and where import of utility
//libraries such as glib would be problematic

#include "cci.h"
#include "cci_mini_except.h"
#include "cci_memory_utils.h"
#include "cci_mini_assert.h"
#include "cci_mini_trace.h"

#define T cci_mini_list_t
typedef struct T *T;

//------------------------------------------------------------------------
extern T cci_mini_list_append( T list , T tail );
//------------------------------------------------------------------------
extern T cci_mini_list_copy( T list );
//------------------------------------------------------------------------
extern T cci_mini_list_list( void_ptr x , ... );
//------------------------------------------------------------------------
extern T cci_mini_list_pop( T list , void_ptr* data );
//------------------------------------------------------------------------
extern T cci_mini_list_push( T list , void_ptr x );
//------------------------------------------------------------------------
extern T cci_mini_list_reverse( T list );
//------------------------------------------------------------------------
extern int cci_mini_list_length ( T list );
//------------------------------------------------------------------------
extern void cci_mini_list_free( T *list );
//------------------------------------------------------------------------
extern void cci_mini_list_map( T list ,
                          void apply( void_ptr *x , void_ptr cl ) ,
                          void_ptr cl );
//------------------------------------------------------------------------
extern void_ptr* cci_mini_list_to_array( T list , void_ptr end );

#undef T


