/// except.c william k. johnson 2015
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "cci/cci_mini_except.h"
#define T except_T

except_frame *except_stack = NULL;

//reference macro in chromatic_expansion.h
//-------------------------------------------------------------------------
///raise
void except_raise( const T *e ,
                   const char *file ,
                   int line )
{

            except_frame *p = except_stack;

        	assert( e );
	        if ( p == NULL )
            {
		        fprintf( stderr , "uncaught exception" );
		        if ( e->reason ) { fprintf( stderr , " %s" , e->reason ); }
                else { fprintf( stderr , " at 0x%p", e ); }

                if ( file && line > 0 ) { fprintf( stderr , " raised at %s:%d\n", file , line ); }

                fprintf( stderr , "aborting...\n" );
        		fflush( stderr );
		        abort();
	        }

            p->exception = e;
	        p->file = file;
	        p->line = line;

           	except_stack = except_stack->prev;
            longjmp( p->env, except_raised );
}




