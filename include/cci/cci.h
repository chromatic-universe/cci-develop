//cci.h william k. johnson 2015
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
#include <chromatic_expansion.h>
#include <chromatic_types.h>
//glib
#include <glib.h>


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
typedef void* void_ptr;


