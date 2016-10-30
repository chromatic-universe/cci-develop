/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2016.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/


// william k. johnson chromatiuc universe 2016

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdarg.h>
#include <string.h>


//bit-mask values for 'flags' argument of becomeDaemon()
//don't chdir("/")
#define BD_NO_CHDIR           01
/* Don't close all open files */
#define BD_NO_CLOSE_FILES     02
//don't reopen stdin, stdout, and  stderr to /dev/null
#define BD_NO_REOPEN_STD_FDS  04
//don't do a umask(0)
#define BD_NO_UMASK0         010
//maximum file descriptors to close if
//ysconf(_SC_OPEN_MAX) is indeterminate
#define BD_MAX_CLOSE  8192



typedef FILE* q_file_ptr;
extern q_file_ptr log_fd;

//wkj 2016 chromatic universe
//------------------------------------------------------------------------------
extern int become_daemon( int flags );
//------------------------------------------------------------------------------
extern void deactivate( int sig );
//-------------------------------------------------------------------------------------------------
extern void _L( const char* segment ,
                const char* log_level ,
                const char* atom );

