//cci_mini_fuser.c william k. johnson 2015

#include "cci/fuser/cci_mini_fuser.h"

static const char *cci_str = "cci_mini_fuser\n";
static const char *cci_path = "/cci_mini_fuser";

//-----------------------------------------------------------------------
void cci_fullpath( char fpath[PATH_MAX] ,
                   const char* path )
{
     strcpy(fpath ,
             CCI_DATA->root_dir);
     strncat( fpath ,
              path ,
              PATH_MAX );
}
//-----------------------------------------------------------------------
int cci_getattr( const char* path , struct stat* stbuf )
{
    return 0;
}

//------------------------------------------------------------------------
int cci_readdir( const char* path ,
                        void_ptr buf ,
                        fuse_fill_dir_t filler ,
           	            off_t offset ,
                        struct fuse_file_info* fi )
{
    int retstat = 0;
    DIR *dp;
    struct dirent *de;

    // once again, no need for fullpath -- but note that I need to cast fi->fh
    dp = (DIR *) (uintptr_t) fi->fh;

    // Every directory contains at least two entries: . and ..  If my
    // first call to the system readdir() returns NULL I've got an
    // error; near as I can tell, that's the only condition under
    // which I can get an error from readdir()
    de = readdir(dp);
    if (de == 0) {
	    return retstat;
    }

    // Thiis will copy the entire directory into the buffer.  The loop exits
    // when either the system readdir() returns NULL, or filler()
    // returns something non-zero.  The first case just means I've
    // read the whole directory; the second means the buffer is full.
    do
    {
    	if (filler(buf, de->d_name, NULL, 0 , 0) != 0)
        {
	        return -ENOMEM;
	    }
    } while ((de = readdir(dp)) != NULL);

    //log_fi(fi);

    return retstat;
}

//------------------------------------------------------------------------
int cci_open( const char *path ,
              struct fuse_file_info* fi )
{

    int retstat = 0;
    int fd;
    char fpath[PATH_MAX];

    cci_fullpath( fpath , path );

    fd = open( fpath , fi->flags );
    if ( fd < 0 )
	//retstat = bb_error("bb_open open");

    fi->fh = fd;
    //log_fi(fi);

    return retstat;

}

//------------------------------------------------------------------------
int cci_read( const char *path ,
                     char* buf ,
                     size_t size ,
                     off_t offset ,
       		         struct fuse_file_info* fi )
{
    return 0;
}

//------------------------------------------------------------------------
int cci_mkdir( const char* path ,
               mode_t mode )
{
     int retstat = 0;
     char fpath[PATH_MAX];

     cci_fullpath( fpath , path );

     retstat = mkdir( fpath , mode );
     //if (retstat < 0) { retstat = bb_error( "bb_mkdir mkdir" );

     return retstat;
}





