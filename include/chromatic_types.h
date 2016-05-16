/*
 * chromatic_types.h
 *
 *  Created on: Aug 26, 2015
 *      Author: wiljoh
 */

#pragma once

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


//types
typedef FILE file_handle;
typedef char* string;
typedef enum { False , True } boolean;

typedef struct string_list
{
    char** elements;
    char* base_string;
    int length;
}string_list;

//external linkage
//if this is null , write to stderr
extern file_handle* error_log;
//set to \c 's' to abort program
extern const char error_mode;
