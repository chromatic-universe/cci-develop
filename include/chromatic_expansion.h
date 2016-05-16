//chromatic_expansion.h william k. johnson 2014

#pragma once

//inline expansion
//----------------------------------------------------------------------------------------
//assertion handler
#define stop_if( assertion , error_action , ... ) \
		{					\
			if( assertion ) \
			{				\
				fprintf( error_log ? error_log : stderr , __VA_ARGS__ ); \
				fprintf( error_log ? error_log : stderr , "\n" ); \
							\
				if ( error_mode == 's') { abort(); } else { error_action; } \
							\
			}				\
		}					\

//----------------------------------------------------------------------------------------
#define double_increment( a , b ) \
		do	\
		{					  \
			(a)++;	  \
			(b)++;		  \
		}				  \
		while( 0 )

//----------------------------------------------------------------------------------------
#define double_decrement( a , b ) \
		do					  \
		{					  \
			( a )--;		  \
			( b )--;		  \
		}					  \
		while( 0 )

//----------------------------------------------------------------------------------------
//while loop is for proper expansion on if conditional statements. trailing else without braces
//must be handled by user
#define down_and_up( a , b ) \
		do					 \
		{					 \
			(a)--;		 \
			(b)++;		 \
		}					 \
		while( 0 )

//----------------------------------------------------------------------------------------
//while loop is for proper expansion on if conditional statements. trailing else without braces
//must be handled by user
#define up_and_down( a , b ) \
		do					 \
		{					 \
			(a)++;		 \
			(b)--;		 \
		}					 \
		while( 0 )

//----------------------------------------------------------------------------------------
//c++ like stream - for c++ programmers , assume function call to asprintf is the  ostream << operator
//stream input must be initialized to NULL
//needed because extended string is at a new memory location
//asprintf handles memory allocation for original string
//extended string must be freed here
#define string_stream( stream , ... ) \
		{	                    		\
			string extend_stream = ( stream ); \
			asprintf( &( stream ), __VA_ARGS__ ); \
			free( extend_stream );	    \
		}
//----------------------------------------------------------------------------------------
//plaform max bits
#define bit_max(a) \
    {\
	a = 64;\
	if( UINTPTR_MAX == 0xffffffff ) \
	{\
	    a = 32;\
	}\
    }

//----------------------------------------------------------------------------------------
//libc version
#define libc_version( version ) \
    {\
	      size_t n; \
	      \
	      (n) = confstr(_CS_GNU_LIBC_VERSION , NULL, (size_t) ( 0 ) ); \
	      ( version ) = malloc( n ); \
	      if ( ( version ) == NULL)\
	      {\
		  abort();\
	      }\
	      confstr( _CS_GNU_LIBC_VERSION, ( version ), ( n ) );\
    }
//----------------------------------------------------------------------------------------
//max path name
#define max_directory_path( limit )\
	     ( limit ) = sysconf( _PC_PATH_MAX );


//exception
#define _raise(e) except_raise(&(e), __FILE__, __LINE__)
#define reraise except_raise(except_frame.exception, \
	except_frame.file, except_frame.line)
#define return_ switch (except_stack = except_stack->prev,0) default: return
#define try do { \
	volatile int except_flag; \
	except_frame except_frame; \
	except_frame.prev = except_stack; \
	except_stack = &except_frame;  \
	except_flag = setjmp(except_frame.env); \
	if (except_flag == except_entered) {
#define except(e) \
		if (except_flag == except_entered) except_stack = except_stack->prev; \
	} else if (except_frame.exception == &(e)) { \
		except_flag = except_handled;
#define else_ \
		if (except_flag == except_entered) except_stack = except_stack->prev; \
	} else { \
		except_flag = except_handled;
#define finally \
		if (except_flag == except_entered) except_stack = except_stack->prev; \
	} { \
		if (except_flag == except_entered) \
			except_flag = except_finalized;
#define end_try \
		if (except_flag == except_entered) except_stack = except_stack->prev; \
		} if (except_flag == except_raised) reraise; \
} while (0)

