 //chromatic_c_test.c  william k. johhnson

#include <chromatic_expansion.h>
#include <chromatic_c_test.h>

#include <cci/cci_mini_except.h>
#include <cci/cci_mini_assert.h>
#include <cci/cci_memory_utils.h>
#include <cci/cci_utils.h>
#include <cci/service/cci_mini_kafka.h>
#include <cci/service/cci_mini_cassandra.h>

const int long_str_len = 24;
const int short_str_len = 6;

//------------------------------------------------------------------------------------------
void dict_setup( dfixture* fx , gconstpointer test_data )
{

	memset( fx->text_1 , '\0' , sizeof( fx->text_1  ) );
	memset( fx->text_2 , '\0' , sizeof( fx->text_1  ) );
	memset( fx->text_3 , '\0' , sizeof( fx->text_1  ) );
	strcpy( fx->text_1 , "The Original Corny snaps!");
	strcpy( fx->text_2 , "The Original Corny snaps!");
	strcpy( fx->text_3 , "Snaps!");

}

//------------------------------------------------------------------------------------------
void dict_teardown( dfixture* fx , gconstpointer test_datea )
{
	//
}

//------------------------------------------------------------------------------------------
void test_compare_equal( dfixture* fx , gconstpointer ignored )
{
	g_assert( compare_str( ( string) fx-> text_1 , (string) fx->text_2 ) );
}
//------------------------------------------------------------------------------------------
void test_not_compare_equal( dfixture* fx , gconstpointer ignored )
{
	g_assert( !compare_str( ( string) fx-> text_1 , (string) fx->text_3 ) );
}

except_T allocate_failed = { "The Original Corny Snaps" };
void* allocate ( unsigned n )
{
    /*void* new = malloc( n ) ;
    if ( new )
    {
        return new;
    }*/
    //_raise( allocate_failed );

    //assert( 0 );
    void* new = NULL;

    try
      printf( "blase\n" );
      _raise( allocate_failed );
    except( allocate_failed )
      printf( "error in allocate!\n" );
    end_try;

    return ( new );

}

int main( int argv , char* argc[] )
{
    allocate( 11 );
	/*char out_str[20] = "blase";
	//string str = "blase";
	//size_t st = len_str( str );

	//printf( "c99_utils length = %d\n" , st );
	//int_to_str( out_str , 1234i );
	//printf( "%s\n" , out_str );

	char* version;
	libc_version( version );
	int limit;
	max_directory_path( limit );
	printf( "max directory path = %d\n" , limit );

	string in_stream = NULL;
	string_stream( in_stream  , "The ");
	string_stream( in_stream  , "%sOriginal" , in_stream );
	string_stream( in_stream  , "%sCorny" , in_stream );
	string_stream( in_stream  , "%sSnaps!\n" , in_stream );

	printf( "%s" , in_stream );

       // double_increment( 1 , 2 );
	//printf( "%i\n" , dw );
	 int a = 0;
	 int b = 1;
	 double_increment( a , b );
	 up_and_down( a , b );
	 down_and_up( a , b );
	 double_increment( a , b );
	 boolean b_ret;
	 bit_max( b_ret );
	 printf( "max_bits = %d\n" , b_ret );
	 b_ret = is_unique_chars_in_str( out_str );
	 string f = "/home/wiljoh/sshfs.py";
	 string textstr = text_string_from_file( f  );
	 a = count_non_blank_lines( textstr );
	 printf( "count of non blank lines in file %s is %d\n" , f , a );
	 g_free( textstr );

	 char reverse_str[256] = "foobar";
	 str_reverse( reverse_str );
	 printf( "%s\n" , reverse_str);
	 b_ret = safe_palindrome( 10201 );
	 printf( "%d\n" , b_ret );
	 b_ret = quick_palindrome( 10201 );
	 printf( "%d\n" , b_ret );*/






	return EXIT_SUCCESS;
}
