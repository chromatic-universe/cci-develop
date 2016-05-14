//cci_memory_utils.c william k. johnson 2015

#include "cci/cci_memory_utils.h"

//exception spec
const except_T mem_failed  = { "allocation failed" };

//The hash macro
///treats the address as a bit pattern, shifts it right three
///bits
#define hash( p , t ) ( ( (unsigned long) (p) >> 3 ) & \
	( sizeof ( t )/sizeof ( ( t )[0])-1 ) )
#define n_descriptors 512
#define n_alloc ( ( 4096 + sizeof ( union align ) - 1 )/ \
	(sizeof ( union align ) ) ) *( sizeof ( union align ) )

//freelist
///list of memory descriptors with dummy head
///list is circular - freelist is the last descriptor
///and its free field points to first descriptor
///free field  is null if allocated , non-null otherwise
static struct descriptor freelist = { &freelist };
//find free structure in hash given its address
///returns null if not found
static struct descriptor *find( const void_ptr ptr )
{
	struct descriptor* bp = htab[hash( ptr , htab )];
	while ( bp && bp->ptr != ptr )
    {
		bp = bp->link;
    }
	return bp;
}

//-----------------------------------------------------------
//no core dump
void cci_zero_core()
{
    struct rlimit rlim;
    rlim.rlim_cur = rlim.rlim_max = 0;

    setrlimit( RLIMIT_CORE, &rlim );
}

//non-checking memory allocation
//
//------------------------------------------------------------------------
void_ptr mem_alloc (  long nbytes , const char *file , int line )
{
    void* ptr = NULL;

    assert( nbytes > 0 );

    ptr = malloc( nbytes );
    if( ptr == NULL )
    {
        if( file == NULL )
        {
           _raise( mem_failed ) ;
        }
        else
        {
           except_raise( &mem_failed , file , line );
        }
    }

    return ptr;

}
//------------------------------------------------------------------------
void_ptr mem_calloc( long count , long nbytes , const char *file , int line )
{
    void* ptr = NULL;

    assert( count > 0 );
    assert( nbytes > 0 );

    ptr = calloc( count , nbytes );
    if( ptr == NULL )
    {
        if( file == NULL )
        {
            _raise( mem_failed );
        }
        else
        {
            except_raise( &mem_failed , file , line );
        }
    }

    return ptr;

}
//------------------------------------------------------------------------
void mem_free( void_ptr ptr , const char *file , int line )
{
    if( ptr ) { free( ptr ); }

}
//------------------------------------------------------------------------
void_ptr mem_resize( void_ptr ptr , long nbytes ,	const char *file , int line )
{
    assert( ptr );
    assert( nbytes > 0 );

    ptr = realloc( ptr , nbytes );
    if( ptr == NULL )
    {
        if( file == NULL )
        {
            _raise( mem_failed );
        }
        else
        {
            except_raise( &mem_failed , file , line );
        }
    }

    return ptr;

}

//------------------------------------------------------------------------
void_ptr cci_mem_chk_alloc( long nbytes , const char *file , int line )
{

    descriptor_ptr  bp = NULL;
	void_ptr ptr;
	assert( nbytes > 0 );

    //round nbytes up to alignment boundary
	nbytes = ( ( nbytes + sizeof ( union align ) - 1 ) /
		( sizeof ( union align ) ) ) * ( sizeof ( union align ) );

    //freelist.free points to the beginning of the free list, which is where
    //the for loop starts.
    for ( bp = freelist.free; bp; bp = bp->free )
    {
        	if (bp->size > nbytes)
            {
                //the first free block whose size exceeds nbytes is
                //used to fill the request. the nbytes at the end of this
                //free block are carved off, and the address of that
                //block is returned after its descriptor  is created
                //and initialized
			    bp->size -= nbytes;
			    ptr = (char *) bp->ptr + bp->size;

			    if ( ( bp = cci_mem_chk_dalloc( ptr , nbytes , file , line ) ) != NULL )
                {
				    unsigned h = hash( ptr , htab );
				    bp->link = htab[h];
				    htab[h] = bp;

				    return ptr;
		    	}
                else
				{
					if ( file == NULL ) { _raise( mem_failed ); }
					else { except_raise( &mem_failed , file , line ); }
				}

		    }
            if ( bp == &freelist )
            {
                //if bp reaches freelist,
                //the list does not hold a block whose size
                //exceeds nbytes. in that case, a new chunk of size
                //plus nbytes is added to the beginning of the free list;
                //it will be visited on the next iteration of the for loop
                //and will be used to fill the request. this new chunk has a
                //descriptor just as if it had been previously allocated and freed:
			    descriptor_ptr newptr = NULL;
			    if ( ( ptr = malloc( nbytes + n_alloc ) ) == NULL
			    ||  ( newptr = cci_mem_chk_dalloc( ptr, nbytes + n_alloc ,
				    	__FILE__ , __LINE__ ) ) == NULL )
                {
					if ( file == NULL ) { _raise( mem_failed ); }
					else { except_raise( &mem_failed , file , line ); }
			    }
                //adjust the pointers of the linked list
                newptr->free = freelist.free;
    			freelist.free = newptr;
		    }
    }

    return NULL;

}

//------------------------------------------------------------------------
void_ptr cci_mem_chk_calloc( long count , long nbytes ,	const char* file , int line )
{

	void_ptr ptr;
	assert( count > 0 );
	assert( nbytes > 0 );
	ptr = cci_mem_chk_alloc( count * nbytes ,
                             file ,
                             line );
	memset( ptr , '\0' , count * nbytes );

	return ptr;

}

//------------------------------------------------------------------------
struct descriptor* cci_mem_chk_dalloc( void_ptr ptr ,
                                       long size ,
                                       const char* file ,
                                       int line )
{
    //decouple allocation of descriptors
    //from memory block allocation
    static struct descriptor *avail = NULL;
    static int nleft = 0;

    if (nleft <= 0 )
    {
        avail = malloc( n_descriptors * sizeof ( *avail ) );
		if ( avail == NULL ) { return NULL; }

        //allocate descriotors
        nleft = n_descriptors;
    }
    avail->ptr  = ptr;
	avail->size = size;
	avail->file = file;
	avail->line = line;
	avail->free = avail->link = NULL;
	nleft--;

	return avail++;

}

//------------------------------------------------------------------------
void_ptr cci_mem_chk_resize( void_ptr ptr ,
                             long nbytes ,
                             const char* file ,
                             int line )
{
    descriptor_ptr bp = NULL;
	void_ptr newptr = NULL;
	assert( ptr );
	assert( nbytes > 0 );

    if ( ( ( unsigned long ) ptr ) % ( sizeof ( union align ) ) != 0
   //test ((unsigned long)ptr)%(sizeof (union align)) != 0 avoids
   //calls to find for those addresses that aren’t multiples of
   //the strictest alignment and thus cannot possibly
   //be valid block pointers.
	|| ( bp = find( ptr ) ) == NULL || bp->free )
    { except_raise( &assert_failed , file , line ); }

    newptr = cci_mem_chk_alloc( nbytes , file , line );
	memcpy( newptr ,
            ptr ,
		    nbytes < bp->size ? nbytes : bp->size );
	cci_mem_chk_free( ptr , file , line );

	return newptr;

}

//------------------------------------------------------------------------
void cci_mem_chk_free( void_ptr ptr , const char* file , int line )
{
    if( ptr  )
    {
        descriptor_ptr bp = NULL;
        //set bp if ptr is  valid address
        //block is deallocated for subsequent
        //reuse by appending it to free list
        if ( ( ( unsigned long )ptr ) % (sizeof ( union align ) ) != 0
        //test ((unsigned long)ptr)%(sizeof (union align)) != 0 avoids
        //calls to find for those addresses that aren’t multiples of
        //the strictest alignment and thus cannot possibly
        //be valid block pointers.
		|| ( bp = find( ptr ) ) == NULL || bp->free )
        { except_raise( &assert_failed , file , line ); }

        bp->free = freelist.free;
        freelist.free = bp;
    }

}












