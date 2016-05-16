/*
 * chromatic_c_utils.h
 *
 *  Created on: Aug 13, 2015
 *      Author: wiljoh
 */

#ifndef CHROMATIC_C_UTILS_H_
#define CHROMATIC_C_UTILS_H_

//ignore constant char* deprecation
#pragma GCC diagnostic ignored "-Wwrite-strings"

//gcc
#include <glib.h>

//c standard
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//test
#include <chromatic_c_utils_test.h>



//types
typedef FILE file_handle;
typedef char* string;
typedef enum { false , true } boolean;

//if this is null , write to stderr
extern file_handle* error_log;

//inline
//----------------------------------------------------------------------------------------
#define stop_if( assertion , error_action , ... ) \
		{					\
			if( assertion ) \
			{				\
				fprintf( error_log ? error_log : stderr , __VA_ARGS__ ); \
				fprintf( error_log ? error_log : stderr , "\n" ); \
							\
				if ( error_mode == 's') { abort(); } else { error_action; } \
							\
			}				\
		}					\

//-----------------------------------------------------------------------------------------
//services
void no_function_call_copy( ptr_char to , ptr_char from );
size_t len_str( const char* str );
boolean compare_str( const char* first , const char* second );

//immutable
//-----------------------------------------------------------------------------------------
static const unsigned long max_bits_32 = 32;//32 bit
static const unsigned long max_bits_64 = 64;//64 bit
static const char space = 32;//ascii
static const char nil = '\0';
//set to \c 's' to abort program
static const char error_mode = '\0';
static const unsigned long char_set_sz = 256;//ascii character set

#endif /* CHROMATIC_C_UTILS_H_ */
