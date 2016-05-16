//cci_access_ctl.h william k. johnson 2015

#pragma once

#include "../cci.h"

#ifndef OPEN_MAX
#define OPEN_MAX 256
#endif

//-----------------------------------------------------------------------------
///open file descriptors using /dev/null
extern int cci_open_dev_null( int fd );
//-----------------------------------------------------------------------------
///close all file and stream descriptors except for standard
extern void cci_sanitize_files( void );
//-----------------------------------------------------------------------------
///check directory tree to see if directory is secure for user
///and superuser only - changes working directory so is not thread safe
///runs only in main thread
extern int cci_is_safe_dir( const char* dir );
//-----------------------------------------------------------------------------
///implementation of peter gutmanns's file wipe algorithm ,
///fsync only i.e. , we assune naively that an fsync call will
///force the file system tp flush file contents
extern int cci_guttman_file_wipe( FILE *f );




