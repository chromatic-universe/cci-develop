//cci_memory_utils.h william k. johnson 2015

//we don't accept zero sizes nor return null pointers

#pragma once

#include "cci.h"
#include "cci_mini_except.h"

//descriptor
///structure for memory descriptor hast table
struct descriptor {
	struct descriptor *free;
	struct descriptor *link;
	const void *ptr;
	long size;
	const char *file;
	int line;
} *htab[2048];

//types
typedef struct descriptor* descriptor_ptr;

//extern allocation utils
extern const except_T mem_failed;

union align {
#ifdef MAXALIGN
	char pad[MAXALIGN];
#else
	int i;
	long l;
	long *lp;
	void* p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
#endif
};

//-----------------------------------------------------------------------
//
//mem_alloc
extern void_ptr mem_alloc ( long nbytes , const char *file , int line );
//
//mem_calloc
extern void_ptr mem_calloc( long count , long nbytes ,	const char *file , int line );
//
//mem_free
extern void mem_free( void_ptr ptr , const char* file , int line );
//
//mem_resize
extern void_ptr mem_resize( void_ptr ptr , long nbytes , const char *file, int line );
//we don't accept zero sizes nor return null pointers

//------------------------------------------------------------------------
//inline
#define cci_alloc(nbytes) \
	mem_alloc((nbytes), __FILE__, __LINE__)
#define cci_calloc(count, nbytes) \
	mem_calloc((count), (nbytes), __FILE__, __LINE__)
#define  cci_new(p) ((p) = cci_alloc((long)sizeof *(p)))
#define cci_new0(p) ((p) = cci_calloc(1, (long)sizeof *(p)))
#define cci_free(ptr) ((void)(mem_free((ptr), \
	__FILE__, __LINE__), (ptr) = 0))
#define cci_resize(ptr, nbytes) 	((ptr) = mem_resize((ptr), \
	(nbytes), __FILE__, __LINE__))

//------------------------------------------------------------------------
//memcheck
//
//memchk alloc
void_ptr cci_mem_chk_alloc( long nbytes , const char* file , int line );
//
//memchk calloc
void_ptr cci_mem_chk_calloc( long count , long nbytes ,	const char* file , int line );
//
//memchk dalloc
static struct descriptor* cci_mem_chk_dalloc( void_ptr ptr ,
                                              long size ,
	                                          const char* file ,
                                              int line );
//
//memcheck resize
void_ptr cci_mem_chk_resize( void_ptr ptr ,
                             long nbytes ,
                             const char* file ,
                             int line );
//
//memcheck free
//
void cci_mem_chk_free( void_ptr ptr , const char* file , int line );
//
//-----------------------------------------------------------
//extern cyber utils , could go in cyber utils , but  we'll put them
//here just because
//-----------------------------------------------------------
//no core dump
extern void cci_zero_core();

