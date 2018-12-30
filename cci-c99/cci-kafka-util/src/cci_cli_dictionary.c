//cci_cli_dicitonary.c      chromatic unvierse  2018         willian k. johnson


#include <cci_cli_dictionary.h>

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>



//-------------------------------------------------------------------------------------
keyval *keyval_new( char *key  , void *value )
{
    keyval *out = malloc(sizeof(keyval));
    *out = (keyval){.key = key, .value=value};
    return out;
}


//-------------------------------------------------------------------------------------
// copy a key/value pair. the new pair has pointers to
// the values in the old pair, not copies of their data.
keyval *keyval_copy( keyval const *in )
{
        keyval *out = malloc ( sizeof( keyval ) );
        *out = *in;

        return out;
}

//-------------------------------------------------------------------------------------
void keyval_free( keyval *in )
{ free( in ); }


//-------------------------------------------------------------------------------------
int keyval_matches( keyval const *in , char const *key)
{  return !strcasecmp( in->key , key ); }






//-------------------------------------------------------------------------------------
void *cci_cli_dictionary_not_found;
//-------------------------------------------------------------------------------------
cci_cli_dictionary *cci_cli_dictionary_new ( void )
{
        static int dnf;

        if ( !cci_cli_dictionary_not_found )
        { cci_cli_dictionary_not_found = &dnf; }

        cci_cli_dictionary *out= malloc (sizeof( cci_cli_dictionary ) );
        *out = (cci_cli_dictionary) {} ;

        return out;
 }


//-------------------------------------------------------------------------------------
static void cci_cli_dictionary_add_keyval( cci_cli_dictionary *in ,
                                   keyval *kv )
{
        in->length++;
        in->pairs = realloc( in->pairs , in->length * sizeof( keyval* ) );
        in->pairs[in->length-1] = kv;
}

//-------------------------------------------------------------------------------------
void cci_cli_dictionary_add( cci_cli_dictionary *in ,
                     char *key ,
                     void *value )
{
        if( !key )
        {
            fprintf( stderr ,
                     "NULL is not a valid key.\n"
                   );
            abort();
        }
        cci_cli_dictionary_add_keyval (in , keyval_new( key , value ) );
}

//-------------------------------------------------------------------------------------
void* cci_cli_dictionary_find( cci_cli_dictionary const *in ,
                       char const *key)
{
        for ( int i=0; i< in->length; i++ )
        {
            if( keyval_matches( in->pairs[i] , key ) )
            {   return in->pairs[i]->value; }
        }
        return cci_cli_dictionary_not_found;
}

//-------------------------------------------------------------------------------------
cci_cli_dictionary* cci_cli_dictionary_copy (cci_cli_dictionary *in )
{
        cci_cli_dictionary *out = cci_cli_dictionary_new();
        for( int i=0; i< in->length; i++ )
        {
            cci_cli_dictionary_add_keyval( out , keyval_copy( in->pairs[i] ) );
        }
        return out;
}

//-------------------------------------------------------------------------------------
void cci_cli_dictionary_free( cci_cli_dictionary *in )
{
        for ( int i=0; i< in->length; i++ )
        {
            keyval_free( in->pairs[i] );
        }
        free( in->pairs );
        free( in );
}
