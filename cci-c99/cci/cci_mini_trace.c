//cci_mini_trace.c  william k. johnson 2015


#include <cci/cci_mini_trace.h>

cci_trace_file_ptr ctfp = NULL;

//------------------------------------------------------------------------
void __attribute__ ( ( constructor ) ) trace_begin( void )
{
    ctfp = fopen( "trace.out", "w" );
}
//------------------------------------------------------------------------
void __attribute__ ( (destructor ) ) trace_end ( void )
{
     if( ctfp != NULL )
     {
        fclose( ctfp );
     }
}
//------------------------------------------------------------------------
void __cyg_profile_func_enter( void *func ,  void *caller )
{
     if( ctfp != NULL )
     {
        fprintf( ctfp ,
                 "e %p %p %lu\n" ,
                 func ,
                 caller ,
                 time( NULL ) );
     }
}
//------------------------------------------------------------------------
void __cyg_profile_func_exit( void *func , void *caller )
{
      if( ctfp != NULL )
      {
        fprintf( ctfp ,
                 "x %p %p %lu\n" ,
                 func ,
                 caller ,
                 time( NULL ) );
      }
}
