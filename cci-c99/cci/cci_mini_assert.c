//cci_assert.c william k. johnson 2015
//
//our assert has same prototype of standard
//so we can include both headers
#include "cci/cci_mini_assert.h"

const except_T assert_failed = { "assertion failed" };

//----------------------------------------------------------------
void (assert)( int e )
{
	assert( e );
}
