/*
 *
 ============================================================================
 Name        : chromatic_c99_util.c
 Author      : William K. Johhnson
 Version     :
 Copyright   : copyright 2015
 Description : utilities
 ============================================================================
 */

#include <cci/cci_utils.h>
#include <chromatic_types.h>
//inline header
#include <chromatic_expansion.h>

//set to \c 's' to abort program
const char error_mode = 's';
//if this is null , write to stderr
file_handle* error_log = NULL;
//---------------------------------------------------------------------------
size_t len_str( string str )
{
	size_t i;
	const string temp_str = str;

	for( i = 0; temp_str[i]; i++ );

	return ( i );

}

//-----------------------------------------------------------------------------------------
void no_function_call_copy( string to_str , string from_str )
{
	assert( from_str );
	assert( to_str );
	assert( (   len_str( to_str ) ) >= (  len_str( from_str ) ) );

	while( *from_str != nil )
	{
		*to_str = *from_str;
		double_increment( to_str , from_str );
	}
	*to_str = nil;
}

//---------------------------------------------------------------------------
boolean compare_str( const string first_str , const string second_str )
{
	assert( first_str );
	assert( second_str );

	char* first = first_str;
	char* second = second_str;

	while( *first == *second )
	{
		if( ( *first == nil) || ( *second == nil ) )
		{
				break;
		}
		double_increment( first , second );
	}
	return ( ( *first == nil ) && ( *second == nil ) ) ? True : False;

}

//---------------------------------------------------------------------------
boolean compare_str_mem( const string first , const string second )
{
	assert( first && second );

	size_t dw_first = ( len_str( first ) );
	size_t dw_second = ( len_str( second ) );
	int dw = 0;

	if( dw_first == dw_second )
	{
		dw = memcmp( (const void*) first , (const void*) second , dw_first );
	}

	return ( dw == 0 ? True : False );
}

//---------------------------------------------------------------------------
void str_reverse( char begin_str[] )
{
	 assert( begin_str );

	 char temp;
	 char* end_str;

	 end_str = begin_str + len_str( begin_str ) - 1;
	 while( end_str > begin_str )
	 {
		 temp = *end_str;
		 *end_str = *begin_str;
		 *begin_str = temp;

		 down_and_up( end_str , begin_str );
	 }
}

//---------------------------------------------------------------------------
void int_to_str( char int_str[] , int input )
{
	int i , dw_remainder , len = 0 , n;

	n = input;

	while( n != 0 )
	{
		len++;
		n /= 10;
	}

	for( i = 0; i < len; i++ )
	{
		dw_remainder = input % 10;
		input = input / 10;
		int_str[len - ( i + 1 )] = dw_remainder + '0';
	}
	int_str[len] = '\0';
}

//---------------------------------------------------------------------------
int str_to_int( string dw_str )
{
	//input cannot be null
	assert( dw_str );
	//local
	boolean b_is_signed = False;
	int dw_num = 0;

	//signed
	if( *dw_str == '-') { b_is_signed = True; }

	while( *dw_str != 0 )
	{
	   //is it a string representation of a digit?
	   assert( *dw_str >= '0' && *dw_str <= '9' );

	   dw_num = ( dw_num * 10 ) + ( *dw_str - '0' );
	   ++dw_str;

	}

    return ( b_is_signed == True ? dw_num *= -1 : dw_num );
}

//---------------------------------------------------------------------------
//array of booleans corresonding to 256 ascii character set. iterating through
//the string each character is set to True as it occurs. If the ascii 'bit' is
//already set , duplicate characters exist.
boolean is_unique_chars_in_str( char str[] )
{
    boolean b_ret = False;
    string local = str;
    //hash for ascii chars
    boolean char_set[char_set_sz];
    for( int i = 0; i < (int) len_str( local ); i++ )
    {
	    int ascii = str[i];
	    if( char_set[ascii] == True )
	    {
		    b_ret = False;
		    break;
	    }
	    char_set[ascii] = True;
    }

    return ( b_ret );
}

//---------------------------------------------------------------------------
//line counter using thread safe strtoken_r
int count_non_blank_lines( string in_string )
{
    int counter = 0;
    string scratch , text , delimiter = "\n";

    //ternary operator is used as first call to tokenize functions is the input string. subsequent calls
    //pass NULL as the first parameter. the scratch address holds the current parsed string
    while( ( text = strtok_r( !counter ? in_string : NULL , delimiter , &scratch ) ) )
    {
	counter++;
    }

    return counter;
}


//---------------------------------------------------------------------------
boolean safe_palindrome( const int dw_palindrome )
{
    int max_bits;
    bit_max( max_bits );
    //two buffers
    char forward_text[max_bits + 1];
    char reverse_text[max_bits + 1];

    //make into str representation
    int_to_str( forward_text , dw_palindrome );

    memcpy( (void*) reverse_text , forward_text , max_bits + 1 );

    //reverse string
    str_reverse( forward_text );

    //compare
    return compare_str( forward_text , reverse_text );

}
//------------------------------------------------------------------------------------
boolean quick_palindrome( const int dw_palindrome )
{
    int max_bits;
    bit_max( max_bits );
    max_bits++;

    //one buffer
    char text[max_bits];

    //make into str representation
    int_to_str( text , dw_palindrome );

    char* forward = text;
    char* reverse = text;
    //move reverse pointerto end
    while( *reverse != '\0' ) ++reverse;
    //back up from null terminator
    --reverse;

    //need identity back and front as pointers move in opposite directions
    while( *forward != '\0' )
    {
	if( *forward != *reverse ) { break; }
	++forward;
	//keep reverse from reversing into undefined memory - forward has an extra click
	*forward ? --reverse : 0;
    }

    return *forward == '\0' ? True : False;

}
//------------------------------------------------------------------------------------
//new string list
string_list* string_list_new( string in_string , char const *delimiters )
{

      string_list* out  = malloc( sizeof( string_list ) );
      *out = (string_list) {.base_string=in_string};
      char* scratch = NULL;
      char* text = strtok_r( in_string , delimiters , &scratch );

      if( !text )
      {
	     out = NULL;
      }
      else
      {
	    while( text )
	    {
	        out->elements = realloc( out->elements , sizeof( char*)*++( out->length ) );
	        out->elements[out->length - 1] = text;
	        text = strtok_r( NULL , delimiters , &scratch );
	    }
      }

      return out;
}
//------------------------------------------------------------------------------------
//free original string. strtok_r has modified it.
void string_list_free( string_list* list )
{
      if( list != NULL )
      {
	  free( list->base_string );
	  free( list->elements);
	  free( list );
      }

}

//---------------------------------------------------------------------------
string text_string_from_file( char const *filename )
{
    string out_str = NULL;
    GError* err = NULL;
    boolean processing = True;

    while( processing == True )
    {
	GIOChannel* in_file = g_io_channel_new_file( filename , "r" , &err );
	if( !in_file )
	{
	    fprintf( stderr , "failed to open file '%s'. \n)", filename );
	    processing = False;
	    break;
	}
	if( g_io_channel_read_to_end( in_file , &out_str , NULL , &err ) != G_IO_STATUS_NORMAL )
	{
	    fprintf( stderr , "found file '%s' but could not read it.\n)", filename );
	    processing = False;
	    break;
	}
	processing = False;
    }

    return out_str;
}


