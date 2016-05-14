//mini_fuser_run.c william k. johnson 2015

#include "cci/fuser/cci_mini_fuser.h"

//------------------------------------------------------------------------
//
//operations adt
static struct fuse_operations cci_oper =
{
    .getattr =  cci_getattr ,
    .readdir =  cci_readdir ,
    .open =     cci_open ,
    .read =     cci_read ,
    .mkdir =    cci_mkdir
};

//---------------------------------------------------------------------------------
static void cci_usage()
{
    fprintf ( stderr ,
              "usage:  ccifs [FUSE and mount options] root_dir mount_point\n"
            );
    abort();
}

//---------------------------------------------------------------------------------
int main( int argc , char* argv[] )
{
    int fuse_stat;
    struct cci_state *cci_data;

    //if root or effectively root
    if ( ( getuid() == 0 ) || (geteuid() == 0 ))
    {
	    //running as root is verboten
        fprintf( stderr ,
                 "running cci_fs as root opens unnacceptable security holes...\n");
	    return 1;
    }

    //command line = no start with hyphen
    if ( ( argc < 3 ) || ( argv[argc-2][0] == '-' ) ||
          ( argv[argc-1][0] == '-' ) )
    {
        //bail to help
	    cci_usage();
    }

    //private data
    cci_data = malloc( sizeof( struct cci_state ) );
    if( cci_data == NULL )
    {
    	perror( "main malloc" );
	    abort();
    }
    cci_data->root_dir = realpath( argv[argc-2] , NULL );
    argv[argc-2] = argv[argc-1];
    argv[argc-1] = NULL;
    argc--;

    // turn over control to fuse
    fprintf( stderr ,
            "about to call fuse_main\n" );

    fuse_stat = fuse_main( argc , argv , &cci_oper, cci_data );
    fprintf( stderr ,
             "fuse_main returned %d\n" ,
             fuse_stat );

    return fuse_stat;

}


