
//xreated on: Aug 13, 2015 author: william k. johnson


#pragma once
//ignore constant char* deprecation
#pragma GCC diagnostic ignored "-Wwrite-strings"

//gcc
#include <glib.h>
#include <gnu/libc-version.h>

//inclusion of asprintf
#define _GNU_SOURCE

//c runtime
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>



//if gcc -Wall , this will quite compiler warnings on error terminate and abort handlers
//of functions with non-void return values
#ifdef __GNUC__
#define NORETURN __attribute__ ( ( __noreturn__ ) )
#else
#define NORETURN
#endif


#if defined (__GLIBC__)
  int asprintf(char **ret, const char *format, ...);
#endif

//types
#include <chromatic_types.h>

//-----------------------------------------------------------------------------------------
//services
//string
void no_function_call_copy( string to , string string );
size_t len_str( string str );
boolean compare_str( const string first , const string second );
boolean compare_str_mem( const string first , const string second );
void str_reverse( char begin_str[] );
void int_to_str( char int_str[] , int input );
int str_to_int( string dw_str );
int count_non_blank_lines( string in_string );
boolean is_unique_chars_in_str( char str[] );
boolean safe_palindrome( const int dw_palindrome );
boolean quick_palindrome( const int dw_palindrome );
//string list
string_list* string_list_new( string in_string , char const * delimiters );
void string_list_free( string_list* strings_in );
//files
string text_string_from_file( char const *filename );
//todo
//proc
//todo
//bits and masks
//todo
//todo
//immutable at file scope , not exported
//-----------------------------------------------------------------------------------------
static const char space = 32;//ascii
static const char nil = '\0';
static const unsigned long char_set_sz = 256;//ascii character set




