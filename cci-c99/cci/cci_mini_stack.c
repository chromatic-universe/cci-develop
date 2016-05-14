
//cc_mini_stack.c william k. johnson 2015
//
//minimal no noise stack implementation
//useful for macros and function pointer
//structures and where import of utility
//library such as glib would be problematic


#include <cci/cci_mini_stack.h>
#define T cci_mini_stack_t

struct T {
	int count;
	struct elem
    {
		void_ptr data;
		struct elem *next;
	} *head;
};

///services
//-----------------------------------------------------------------------------------------
T  cci_mini_stack_new( void )
{
    //init stack header
    T stk;
    cci_new( stk );
    stk->count = 0;
    stk->head = NULL;

    return stk;
}
//-----------------------------------------------------------------------------------------
int cci_mini_stack_empty( T stk )
{
    //boolean is stack empty
    assert( stk );

    return stk->count == 0;

}
//-----------------------------------------------------------------------------------------
void cci_mini_stack_push( T stk , void_ptr data )
{
    //push stack
    struct elem* t;

    assert( stk );
    //new member
    cci_new( t );

    //set data
    t->data = data;
    //old head is next
    t->next = stk->head;
    //new head
    stk->head = t;
    //increment count
    stk->count++;

}
//-----------------------------------------------------------------------------------------
void_ptr cci_mini_stack_pop( T stk )
{
    //pop stack
    void_ptr data;
    struct elem* t;

    assert( stk );
    assert( stk->count > 0 );

    //set new head
    t = stk->head;
    stk->head = t->next;
    stk->count--;

    //get old head data
    data = t->data;
    //free old head
    cci_free( t );

    //return pop data
    return data;

}
//-----------------------------------------------------------------------------------------
void cci_mini_stack_free( T *stk )
{
    //free
    struct elem* t;
    struct elem* u;

    assert( stk && *stk );

    //starting at head , for each member
    //head != null
    //t set to next pointer
    for( t = (*stk)->head; t; t = u )
    {
        //new head
        u = t->next;
        //free old head
        cci_free( t );
    }//until no more

}
//-----------------------------------------------------------------------------------------
void_ptr cci_mini_stack_top( T stk )
{
    //return to )data , do not remove element
    assert( stk );
    assert( stk->count > 0  );

    return stk->head->data;
}

//------------------------------------------------------------------------
int cci_mini_stack_count( T stk )
{
      assert( stk );

      return stk->count;
}

//------------------------------------------------------------------------
void cci_mini_stack_dump( T stk , stack_iterator func )
{
      assert( stk );

      struct elem* esp;

      int dw = 0;
      for( esp = stk->head; esp->next != NULL; esp = esp->next )
      {
          dw = func( esp->data );
      }

}

//------------------------------------------------------------------------
void cci_mini_stack_backtrace( void )
{
     void_ptr frame_addrs[16];
     char** frame_strings;
     size_t backtrace_size;

     backtrace_size = backtrace( frame_addrs , 16 );
     frame_strings = backtrace_symbols( frame_addrs , backtrace_size );
     for ( int i = 0; i < backtrace_size; i++ )
     {
        printf( "%d: [0x%x] %s\n", i, frame_addrs[i], frame_strings[i]);
     }

     free( frame_strings );
}

//------------------------------------------------------------------------
void cci_mini_stack_on_exit( const char* translator_path )
{
     cci_mini_stack_backtrace();
}

//------------------------------------------------------------------------
T cci_mini_stack_copy( const T stk )
{
     //todo
     assert( stk );
     struct elem* esp;

     T ret_stk = cci_mini_stack_new();
     if( ret_stk )
     {
        for( esp = stk->head; esp->next != NULL; esp = esp->next )
        {
            cci_mini_stack_push( ret_stk , esp->data );
        }
     }

     return ret_stk;

}




