// cci_kakfka)sinck.c   william k. johnson   2016



//cci
#include <cci_kafka_async_q.h>

const char* default_url = "tcp://127.0.0.1:7083";

//------------------------------------------------------------------------------------------------
static void display_banner();
//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
int main( int argc , char* argv[]  )
{
            signal( SIGINT , deactivate );
            signal( SIGTERM , deactivate );

            display_banner();

            log_fd = stderr;
            _L( "cli initialization" , "INFO" , "..cci kafka dispatch..chromatic universe 2016" );
            _L( "cli initialization" , "INFO" , "..linux x86-32/64 toolchain using clang 3.71  cc1=gcc 4.9..." );
            _L( "library initialization:.rdkafka version.." , "INFO" , rd_kafka_version_str()  );

            char* m = "the original corny snaps!";
            int handle = dispatch_first_atom( default_url , m  , strlen( m ) + 1 );
             if( -1 == handle )
             {
                 _L( "transport initialization:.." , "ERROR" , "...nvalid handle...." ); \
                  exit( EXIT_FAILURE );
             }

             else
             {
                 dispatch_atom( default_url , m , strlen( m ) + 1   , &handle );
                 dispatch_last_atom( default_url , m , strlen( m  ) + 1  , &handle );
             }


             return 0;

}

//------------------------------------------------------------------------------------------------
void display_banner()
{
        char buffer[31];
        memset( buffer ,(int) '*', 30 );
        buffer[30]='\0';
        fprintf( stderr , "%s", buffer );
        fprintf( stderr , "\t\t\t\t\t%s\n", buffer );
        fprintf( stderr ,
                 "\t\t\t%s" ,
                 "cci kafka q dispatch , chromatic universe 2016\n" );
        fprintf( stderr , "%s", buffer );
        fprintf( stderr , "\t\t\t\t\t%s\n\n", buffer );

}


