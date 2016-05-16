//cci_assert.h william k. johnson 2015
//
//
//as specified by the standard, except that an assertion
//failure raises the exception assert_failed instead of abort
//and does not provide the text of the assert
//
//our intention , ignore diagnostic just for this file
//#pragma GCC diagnostic ignored "-Wmacro-redefined"
//
#pragma once
#include "cci_mini_except.h"
#undef assert
#ifdef NDEBUG
#define assert(e) ((void)0)
#else
extern void assert(int e);
#define assert(e) ((void)((e)||(_raise(assert_failed),0)))
#endif
