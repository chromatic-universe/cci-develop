//cci_except.h william k. johhnson 2015
#pragma once

#include "cci.h"
#include <setjmp.h>
#define T except_T

//use this interface sparingly , the macro interface
//is fragile at runtime. this can be useful if it is
//remembered that exceptions and errors are distinct.
//also can be interesting to use with syscalls , being
//that system trap instructions are essentially exceptions.

//types
typedef struct T
{
    const char* reason;
} T;
typedef struct except_frame except_frame;
struct except_frame {
	except_frame *prev;
	jmp_buf env;
	const char *file;
	int line;
	const T *exception;
};


//enumerations
enum  exception
{
    except_entered = 0 ,
    except_raised ,
    except_handled ,
    except_finalized
};

//external
extern except_frame* except_stack;
extern const except_T assert_failed;

//services
void except_raise( const T* e, const char* file , int line );


#undef T

