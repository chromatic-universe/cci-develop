//cci_mini_stack.h william k. johhnson 2015
#pragma once

#include "cci.h"
#include "cci_assert.h"
#include "cci_memory_utils.h"
//for stack trace
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <execinfo.h>

//definition
#define T cci_mini_stack_t
typedef struct T *T;
typedef int (*stack_iterator)(void *);

//cci interface 'namespace'

//cci_mini_stack
//------------------------------------------------------------------------
extern T cci_mini_stack_new( void );
//------------------------------------------------------------------------
extern int cci_mini_stack_empty( T stk );
//------------------------------------------------------------------------
extern void cci_mini_stack_push( T stk , void_ptr data );
//------------------------------------------------------------------------
extern void_ptr cci_mini_stack_top( T stk );
//------------------------------------------------------------------------
extern void_ptr cci_mini_stack_pop( T stk );
//------------------------------------------------------------------------
extern void cci_mini_stack_free( T *stk );
//------------------------------------------------------------------------
extern int cci_mini_stack_count( T stk );
//------------------------------------------------------------------------
extern void cci_mini_stack_dump( T stk , stack_iterator func );
//------------------------------------------------------------------------
extern void cci_mini_stack_backtrace( void );
//------------------------------------------------------------------------
extern void cci_mini_stack_on_exit( const char* translator_path );
//------------------------------------------------------------------------
extern T cci_mini_stack_copy( const T stk );






#undef T

