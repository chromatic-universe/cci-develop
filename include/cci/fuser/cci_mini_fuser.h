//cci_mini_fuser.h  william k. johnson 2015

#pragma once
#define _POSIX_C_SOURCE 199309
#define FUSE_USE_VERSION 30

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <fuse.h>
#include "cci/cci.h"


struct cci_state {
    FILE* log_file;
    char* root_dir;
};
#define CCI_DATA ((struct cci_state *) fuse_get_context()->private_data)

///helpers
//
//fullpath
//-----------------------------------------------------------------------
void cci_fullpath( char fpath[PATH_MAX] ,
                   const char* path );

///servuces
//get_attr
extern int cci_getattr( const char* path , struct stat* stbuf );
//------------------------------------------------------------------------
//
//readdir
extern int cci_readdir( const char* path ,
                        void_ptr buf ,
                        fuse_fill_dir_t filler ,
           	            off_t offset ,
                        struct fuse_file_info* fi );
//------------------------------------------------------------------------
//
//open
extern int cci_open( const char *path ,
                     struct fuse_file_info* fi );

//------------------------------------------------------------------------
//
//read
extern int cci_read( const char *path ,
                     char* buf ,
                     size_t size ,
                     off_t offset ,
       		         struct fuse_file_info* fi );
//------------------------------------------------------------------------
extern int cci_mkdir( const char* path ,
                      mode_t mode );


