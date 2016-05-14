//cci_access_ctl.c william k. johnson 2015

#include <cci/cyber/cci_access_ctl.h>

//------------------------------------------------------------------------
//dev null redirect
int cci_open_dev_null( int fd )
{
    FILE *f = 0;
    if( !fd ) f = freopen( _PATH_DEVNULL , "rb", stdin );
    else if(fd == 1) f = freopen( _PATH_DEVNULL , "wb", stdout );
    else if(fd == 2) f = freopen( _PATH_DEVNULL , "wb", stderr );
    return ( f && fileno( f ) == fd );

}

//------------------------------------------------------------------------
//sanitize file descriptors
void cci_sanitize_files( void )
{
    ///useful for initialization of daemon processes
    ///and process security
    int fd , fds;
    struct stat st;

    //close all open descriptors other than standard ones are closed
    if( ( fds = getdtablesize() ) == -1 ) { fds = OPEN_MAX; }

    for ( fd = 3; fd < fds; fd++ ) { close( fd ); }
    //verify standard descriptors are open. if not , open using /dev/null.
    for ( fd = 0; fd < 3; fd++ )
    if( fstat( fd ,  &st ) == -1 && ( errno != EBADF ||
                                !cci_open_dev_null( fd ) ) ) { abort(); }


}

//------------------------------------------------------------------------
//safe directory path
int cci_is_safe_dir( const char* dir )
{
    //all the directories in the path must also be protected
    //against any other users writing to them
    DIR *fd = NULL;
    DIR *start = NULL;
    int return_code = -1;
    char new_dir[PATH_MAX + 1];
    uid_t uid;
    struct stat f , l;

    //are we in main thread?
    //gettid() returns the caller's thread id (tid)
    //in a single-threaded process, the thread id is equal
    //to the process id
    #ifdef SYS_gettid
        //we have to roll our own here
        if ( getpid() == syscall( SYS_gettid ) ) { return -1; }
    #endif

    //open
    if ( !( start = opendir( "." ) ) ) { return -1; }
    //stat
    if  ( lstat( dir , &l )  == -1 )
    {
        closedir( start );
        return -1;
    }

    //uid
    uid = geteuid();
    //changing work directory , not thread safe
    do
    {
        if ( chdir( dir ) == -1 ) {  break; }

        //root
        if ( !( fd = opendir( "." ) ) ) { break; }
        if ( fstat( dirfd( fd ) , &f ) == -1 )
        {
            closedir( fd );
            break;
        }
        closedir( fd );

        //compare current dir info to start info
        if( l.st_mode != f.st_mode
                || l.st_ino != f.st_ino
                || l.st_dev != f.st_dev )
        {
            break;
        }
        if( ( f.st_mode & ( S_IWOTH | S_IWGRP ) )
                || ( f.st_uid && f.st_uid != uid ) )
        {
            //not safe
            return_code = 0;
            break;
        }

        //proceed
        dir = "..";
        if ( lstat( dir , &l ) == -1 ) { break; }
        if ( !getcwd( new_dir , PATH_MAX + 1 ) ) { break; }
    }
    while (new_dir[1]);// new_dir[0] will always be a slash

    //ok
    if( !new_dir[1] ) { return_code = 1; }

    //return
    fchdir( dirfd( start ) );
    closedir( start );

    // -1 error , 0 not safe , 1 safe
    return return_code;

}

//------------------------------------------------------------------------
//guttman file wipe
int cci_guttman_file_wipe( FILE *f )
{
    return ( 0  );
}



