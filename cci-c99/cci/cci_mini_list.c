//cci_mini_list.c   william k. johnson 2015


#include <cci/cci_mini_list.h>
#define T cci_mini_list_t

struct T {
	T rest;
	void_ptr first;
};

//------------------------------------------------------------------------
T cci_mini_list_append( T list , T tail )
{
    assert( tail );

    T *ptr_ref = &list;

    //walk to end of list(null)
    while( *ptr_ref ) { ptr_ref = &(*ptr_ref)->rest; }

    //null pointer at end of list assigned to tail
    *ptr_ref = tail;
    //if list itself is null pointer , ptr_ref now
    //points to list , appending to empty list

    return list;
}

//------------------------------------------------------------------------
T cci_mini_list_copy( T list )
{
    T p;
    return p;
}

//------------------------------------------------------------------------
T cci_mini_list_list( void_ptr x , ... )
{
    //untyped list terminated by null - other than char* and void*
    //must be explicitly cast to one or the other
    //made necessary by the var args , i.e. there is
    //no prototype for the va_args( second and
    //subsequent arguments )
    //
    //i.e. a list containing three lists each
    //containing a single node
    //
    // p = cci_mini_list_listlist( cci_mini_list_list( "foo" , NULL ) ,
    //                        (void*) cci_mini_list_list( "bar", NULL ) ,
    //                        (void*) cco_list_list( "baz" , NULL ) ,
    //                        NULL );
    va_list vl;
    //list_ptr starts by pointing to list
    T list , *list_ptr = &list;

    va_start( vl , x );
    for( ; x; x = va_arg( vl , void*) )
    {
        cci_new( *list_ptr );
        (*list_ptr)->first =   x;

        //list_ptr points to rest of list
        //subsequent assignment to list_ptr
        //will append new node
        list_ptr = &(*list_ptr)->rest;
        //breaks on first null assignment to x
    }

    *list_ptr = NULL;
    va_end( vl );

    return list;
}

//------------------------------------------------------------------------
T cci_mini_list_pop( T list , void_ptr* data )
{
    T p;

    if( list )
    {
        //new head
        T head = list->rest;
        //retrieve data
        if( data )  { *data = list->first; }

        //free node
        cci_free( list );

        return head;
    }
    else
    {
        //no op
        return list;
    }

}

//------------------------------------------------------------------------
T cci_mini_list_push( T list , void_ptr x )
{
    //push front new element ,
    //creates new list if T is null
    T list_ptr;

    cci_new( list_ptr );
    assert( list_ptr );

    //first node
    list_ptr->first = x;
    //rest of list
    list_ptr->rest = list;

    return list_ptr;
}

//------------------------------------------------------------------------
T cci_mini_list_reverse( T list )
{
    assert( list );

    T head = NULL;
    T next;

    for( ; list; list = next )
    {
        next = list->rest;
        list->rest = head;
        head = list;
    }

    return head;
}
//------------------------------------------------------------------------
int cci_mini_list_length ( T list )
{
    int n;
    for( n = 0; list; list = list->rest )  { n++; }

    return n;
}
//------------------------------------------------------------------------
void cci_mini_list_free( T *list )
{
    assert( list );

    T next;

    //release list items
    for( ; *list; *list = next )
    {
        next = (*list)->rest;
        cci_free( *list );
    }
    //list pointer itself is not released
}
//------------------------------------------------------------------------
void cci_mini_list_map( T list ,
                   void apply( void_ptr *x , void_ptr cl ) ,
                   void_ptr cl )
{
    //
}
//------------------------------------------------------------------------
void_ptr* cci_mini_list_to_array( T list , void_ptr end )
{
    return NULL;
}


