/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2016.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

// william k. johnson chromatic universe 2016

#include <cci_daemon.h>


q_file_ptr log_fd = NULL;

typedef struct  { int sig;  char* moniker; } signal_to_string;
signal_to_string signal_monikers[] =
{
    { SIGINT , "SIGINT" } ,
    { SIGTERM , "SIGTERM" }
};
static void signal_moniker( int sig , char* selected );


//-------------------------------------------------------------------------------------------------
void signal_moniker( int sig , char* selected )
{
        signal_to_string* ss;

        for( ss = signal_monikers;
                ss != signal_monikers + sizeof(signal_monikers) / sizeof(signal_monikers[0]);
                    ss++ )
        { if( ss->sig == sig ) { strcpy( selected , ss->moniker  ); } }
        //not found is a no-op
}

//-------------------------------------------------------------------------------------------------
void deactivate( int sig )
{

        if( log_fd  )
        {
            char str_signal[32];
            memset( str_signal , '\0', 32);
            signal_moniker( sig , str_signal );

            _L( "deactivation..." ,  "WARNING" , (const char*) str_signal );
        }
        exit( sig );

}



//-----------------------------------------------------------------------------
int become_daemon( int flags )
{
            int maxfd , fd;

            // become background process

            switch ( fork() )
            {
                //child falls through...
                case -1: return -1;
                case 0:  break;
                //while parent terminates
                default:  exit( EXIT_SUCCESS );
            }



            // become leader of new session
            if ( setsid() == -1 ) { return -1; }

            //ensure we are not session leader
            switch  ( fork() )
            {
                case -1: { return -1; }
                case 0:  break;
                default: exit( EXIT_SUCCESS );
            }

            // clear file mode creation mask
            if ( !( flags & BD_NO_UMASK0 ) ) { umask( 0 ); }
            // change to root directory
            if ( !( flags & BD_NO_CHDIR ) ) { chdir("/");  }
            // close all open files
            if ( !( flags & BD_NO_CLOSE_FILES ) )
            {
                // close all open files
                maxfd = sysconf( _SC_OPEN_MAX );
                // Limit is indeterminate...
                if ( maxfd == -1 ) {  maxfd = BD_MAX_CLOSE; }// so take a guess/

                for ( fd = 0; fd < maxfd; fd++ ) { close( fd ); }
            }


            //reopen standard fd's to /dev/null
            if ( !( flags & BD_NO_REOPEN_STD_FDS ) )
            {
                close( STDIN_FILENO );
                fd = open( "/dev/null" , O_RDWR ) ;

                //fd' should be 0
                if ( fd != STDIN_FILENO ) { return -1; }
                if ( dup2( STDIN_FILENO , STDOUT_FILENO ) != STDOUT_FILENO ) { return -1; }
                if ( dup2( STDIN_FILENO , STDERR_FILENO ) != STDERR_FILENO ) { return -1; }
            }

            return 0;

}

//-------------------------------------------------------------------------------------------------
void _L( const char* segment ,
         const char* log_level ,
         const char* atom
        )
{
       	struct timeval tv;
    	gettimeofday( &tv , NULL );

        fprintf(  log_fd ,
                  "\033[22;32m%u.%03u CCI_KAFKA_Q-\033[0m(%s)-%s: %s\n" ,
		          (int) tv.tv_sec ,
                  (int) ( tv.tv_usec / 1000 ) ,
		          log_level ,
                  segment ,
                  atom
               );

}


