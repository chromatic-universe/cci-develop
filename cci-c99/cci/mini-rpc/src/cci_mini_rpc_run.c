//cci_mini_rpc_run.c   william k. johnson 2015

#include <stdio.h>
#include <assert.h>
#include <glib-object.h>

#include <thrift/c_glib/protocol/thrift_binary_protocol.h>
#include <thrift/c_glib/transport/thrift_buffered_transport.h>
#include <thrift/c_glib/transport/thrift_socket.h>

#include "cci_mini_clang_rpc.h"

typedef cci_mini_clang_rpcIf* mini_rpc_client_ptr;
typedef ThriftSocket*    socket_ptr;
typedef ThriftTransport* transport_ptr;
typedef ThriftProtocol*  protocol_ptr;


//takes list of pointers delimited by compound literal
//containing a single int. condition looks only at pointers
//pointers are typed
#define fn_apply(type,fn, ... ) \
        {                       \
            void* apply_stop_flag = (int[]) {0}; \
            type** apply_list = (type*[]){__VA_ARGS__,apply_stop_flag}; \
            for(int i=0; apply_list[i] != apply_stop_flag; i++) \
                fn(apply_list[i]); \
        }
//free all
#define free_all_refs(...) fn_apply(void, g_object_unref , __VA_ARGS__);

//-------------------------------------------------------------
static void init_transport( socket_ptr* ptr_s ,
                            transport_ptr* ptr_t ,
                            protocol_ptr* ptr_p );


int main( int argc , char* argv[] )
{
    //transport interfaces
    socket_ptr sp;
    transport_ptr tp;
    protocol_ptr pp;

    int exit_status = 0;

    //client ptr
    mini_rpc_client_ptr rpc_client_ptr;

    //glib error
    GError* error = NULL;
    //exception
    invalid_clang_op* invalid_operation_ptr = NULL;

#if (!GLIB_CHECK_VERSION (2, 36, 0))
    g_type_init ();
#endif

    //init transport
    init_transport( &sp , &tp , &pp );
    //open transport
    thrift_transport_open ( tp , &error);
    //instantiate client
    rpc_client_ptr = g_object_new( TYPE_CCI_MINI_CLANG_RPC_CLIENT ,
                                   "input_protocol" ,
                                   pp ,
                                   "output_protocol" ,
                                   pp ,
                                   NULL );
    assert( rpc_client_ptr );

    //service call
    gchar* istr = g_malloc( 1024);
    gchar* ostr = "the_original_corny_snaps";

    cci_mini_clang_rpc_client_perform_diag( rpc_client_ptr ,
                                            &istr ,
                                            ostr ,
                                            &error );
    {
        printf( "perform diag returned %s....\n" , istr );
    }
    //free remote reference
    g_free( istr );

    if( error )
    {
        printf ( "error: %s\n" , error->message );
        g_clear_error ( &error );

        exit_status = 1;
    }

    //deinit
    free_all_refs( rpc_client_ptr ,
                   sp ,
                   tp ,
                   pp );

    return exit_status;
}

//-------------------------------------------------------------
void init_transport( socket_ptr* ptr_s ,
                     transport_ptr* ptr_t ,
                     protocol_ptr* ptr_p )
{
    *ptr_s = g_object_new ( THRIFT_TYPE_SOCKET,
                           "hostname" ,
                           "192.168.32.136" ,
                           "port" ,
                           9090 ,
                           NULL );
    *ptr_t = g_object_new ( THRIFT_TYPE_BUFFERED_TRANSPORT,
                           "transport" ,
                           *ptr_s ,
                           NULL );
    *ptr_p = g_object_new ( THRIFT_TYPE_BINARY_PROTOCOL,
                           "transport" ,
                           *ptr_t ,
                           NULL );

}

