// cci_async_q.c   william k. johnson 2016

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <arpa/inet.h>

//cci
#include <cci_kafka_async_q.h>


// MAXJOBS is a limit on the on the number of outstanding requests we can queue
#define MAXJOBS 100

//
uint64_t milliseconds (void)
{
            struct timeval tv;
            gettimeofday (&tv, NULL);
            return ( ( ( uint64_t)tv.tv_sec * 1000 ) + ( ( uint64_t)tv.tv_usec / 1000) );
}

// ------------------------------------------------------------------------------------------------
int kafka_server_q( const char* url  , kafka_context_ptr kc )
{
                    assert( kc );
                    assert( url );

                    int fd;
                    struct work *worklist = NULL;
                    int npending = 0;
                    //throttle in milleseconds
                    uint32_t throttle = 250;

                    char placeholder[1];
                    int siz = snprintf( placeholder , sizeof placeholder , "%i" , throttle  );
                    char* representation = malloc( siz + 1 );
                    sprintf( representation, "%i", throttle );
                    _L( "transport initialization-queue throttle in milliseconds " , "INFO" ,  representation );
                    free( representation );



                    // create socket
                    fd = nn_socket( AF_SP_RAW ,
                                    NN_REP );
                    if ( fd < 0 )
                    {
                        _L( "transport initialization-nm_socket" , "ERROR" ,  nn_strerror( nn_errno () ) );

                        return ( -1 );
                    }
                    _L( "transport initialization-nm_socket" , "INFO" ,  "..ok.." );


                    // bind to the URL.  This will bind to the address and listen
                    // synchronously; new clients will be accepted asynchronously
                    // without further action from the calling program.
                    if ( nn_bind ( fd , url ) < 0 )
                    {
                        _L(  "transport initialization-nn_bind" , "ERROR" , nn_strerror( nn_errno () ) );
                        nn_close ( fd );

                        return (-1);
                    }
                    _L( "transport initialization-nm_bind...ok..endpoint.." , "INFO" ,  url );
                    _L( "async initialization.." , "INFO" ,  "beginning async io loop..."  );
                    //perform
                    for ( ;; )
                    {
                        int rc;
                        int timeout;
                        uint64_t now;
                        struct work *work, **srch;
                        uint8_t *body;
                        void *control;
                        struct nn_iovec iov;
                        struct nn_msghdr hdr;
                        struct nn_pollfd pfd[1];


                        // figure out if any work requests are finished
                        timeout = -1;
                        while (  (work = worklist ) != NULL )
                        {

                            now = milliseconds ();
                            if ( work->expire > now )
                            {
                                timeout = ( work->expire - now );
                                break;
                            }
                            worklist = work->next;
                            npending--;
                            _L( "working queue.." , "INFO" , "...doing work..sending msg." );
                            rc = nn_sendmsg ( fd ,
                                              &work->request ,
                                              NN_DONTWAIT );
                            if ( rc < 0 )
                            {
                                _L( "aysnc operation..nn_sendmsg" , "ERROR" , nn_strerror ( nn_errno () ) );
                                 nn_freemsg ( work->request.msg_control );
                                 nn_freemsg( work->payload );
                            }
                            // dispatch kafka atom
                            ex_parte_atomic_production( kc ,
                                                        work->payload ,
                                                         strlen( (char*) work->payload )  + 1 );

                            nn_freemsg( work->payload );
                            free ( work );
                        }

                        // this check ensures that we don't allow more than a set limit
                        if ( npending >= MAXJOBS )
                        {
                            nn_poll ( pfd ,
                                      0,
                                      timeout );
                            continue;
                        }

                        pfd[0].fd = fd;
                        pfd[0].events = NN_POLLIN;
                        pfd[0].revents = 0;
                        nn_poll (pfd, 1, timeout);

                        if ( ( pfd[0].revents & NN_POLLIN) == 0 )  { continue; }

                        // so there should be a message waiting for us to receive.
                        // we andle it by parsing it, creating a work request for it,
                        //and adding the work request to the worklist.
                        memset (&hdr, 0, sizeof (hdr));
                        control = NULL;
                        iov.iov_base = &body;
                        iov.iov_len = NN_MSG;
                        hdr.msg_iov = &iov;
                        hdr.msg_iovlen = 1;
                        hdr.msg_control = &control;
                        hdr.msg_controllen = NN_MSG;

                        rc = nn_recvmsg ( fd , &hdr , 0 );
                        if ( rc < 0 )
                        {
                            _L( "aysnc operation..nn_recv" , "ERROR" , nn_strerror( nn_errno () ) );
                            break;
                        }

                        _L( "async operation" , "INFO" , "received message...emplaced to work queue.." );

                        work = malloc( sizeof (*work) );
                        if ( work == NULL )
                        {
                            _L( "aysnc operation..heap alloc.." , "ERROR" , strerror( errno ) );
                            break;
                        }
                        int l  = strlen( (char*) body ) + 1;
                        work->payload = nn_allocmsg( l , 0 );
                        strcpy( work->payload  , (char*) body ) ;

                        nn_freemsg( body );

                        work->expire = milliseconds () + throttle;
                        work->control = control;
                        work->request.msg_iovlen = 0;
                        work->request.msg_iov = NULL;
                        work->request.msg_control = &work->control;
                        work->request.msg_controllen = NN_MSG;

                        //insert the work request into the list in order.
                        srch = &worklist;
                        for (;;)
                        {
                            if ( (*srch == NULL) || ( (*srch)->expire > work->expire ) )
                            {
                                work->next = *srch;
                                *srch = work;
                                npending++;
                                break;
                            }
                            srch = &(( *srch)->next );
                        }
                    }

                    //this may wind up orphaning requests in the queue.   We are going
                    //to exit with an error anyway, so don't worry about it


                    nn_close ( fd );
                    return ( -1 );
}

//-------------------------------------------------------------------------------------------------
int kafka_client_q ( const char* url , const char* packet , int* rfd  , int len )
{
                    int rc;
                    void *msg;
                    struct nn_msghdr hdr;
                    struct nn_iovec iov;
                    uint64_t start;
                    uint64_t end;


                    // reuse the descriptor
                    if(  *rfd == -1  )
                    {

                        *rfd = nn_socket (AF_SP, NN_REQ);
                        if ( *rfd < 0 )
                        {
                            _L( "transport initialization..nn_socket" ,
                                 "ERROR" ,  nn_strerror (nn_errno () ) );
                            return (-1);
                        }
                    }
                     _L( "transport initialization.." , "INFO" , "..socket ok.." );


                    if ( nn_connect ( *rfd , url) < 0 )
                    {
                         _L( "transport initialization..nn_socket connect failed" ,
                                 "ERROR" ,  nn_strerror (nn_errno () ) );
                         _L( "transport initialization..check server at " ,
                                 "ERROR" ,  url );
                        nn_close( *rfd );
                        return ( -1 );
                    }
                    _L( "transport initialization.." , "INFO" , "..connected.." );

                    // send payload , we let the libary allocate and deallocate
                    // buffers
                    start = milliseconds ();
                    _L( "transport send..." ,  "INFO" ,  url );
                    msg = nn_allocmsg( len , 0 );
                    if( msg == NULL )
                    {
                         _L( "transport send..nn_allocmsg failed" ,
                                 "ERROR" ,  nn_strerror (nn_errno () ) );
                         exit( 1 );
                    }
                    _L( "transport send..." ,  "INFO" ,  "..heap alloc..." );
                    strcpy( msg , packet );
                    iov.iov_base = &msg;
                    iov.iov_len = NN_MSG;
                    memset ( &hdr , 0 , sizeof (hdr) );
                    hdr.msg_iov = &iov;
                    hdr.msg_iovlen = 1;

                    if ( nn_sendmsg(  *rfd ,   &hdr , NN_DONTWAIT ) == -1 )
                    {
                         _L( "transport send..." ,  "ERROR" ,  nn_strerror ( nn_errno () ) );
                        nn_close ( *rfd );
                        return ( -1 );
                    }

                    _L( "transport receive...nn_recv " , "INFO" ,  url );
                    rc = nn_recv ( *rfd ,   &msg , sizeof (msg) ,  0 );
                    if ( rc < 0 )
                    {
                        _L( "transport receive..nn_recv. " , "ERROR" ,  nn_strerror( nn_errno () ) );
                        nn_close ( *rfd );
                        return ( -1 );
                    }

                    end = milliseconds();

                    _L( "transport transaction... " , "INFO" ,  url );

                    char buf[256];
                    sprintf( buf , "..request took %u milliseconds..." , (uint32_t) ( end - start ) );
                     _L( "transport transaction... " , "INFO" ,  buf );


                    return ( 0 );
}

//------------------------------------------------------------------------
int dispatch_first_atom( const char* url , const char* packet , int len )
{
         int handle = -1;

         int ret = kafka_client_q( url , packet , &handle , len );
         if( ret == -1 )
         {
             _L( "dispatch production.." , "ERROR" ,  "atomic production failed..."  );
             return ret;
         }

         return handle;
}

//------------------------------------------------------------------------
void dispatch_atom( const char* url , const char* packet , int len , int* handle )
{
         kafka_client_q( url , packet ,  handle , len );
}

//------------------------------------------------------------------------
void dispatch_last_atom( const char* url , const char* packet , int len , int* handle )
{
         kafka_client_q( url , packet ,  handle , len );
         //library closes handle
          nn_close ( *handle );
         _L( "dispatch production.." , "WARNING" ,  "...production context has been closed.."  );
}



