//cci_cli_cci_cli_dictionary.h   chromatic universe 2018    william k. johnson

#pragma once




//keyvak
typedef struct keyval
{
   char *key;
   void *value;
} keyval;

//-------------------------------------------------------------------------------------
keyval *keyval_new( char *key , void *value) ;
//-------------------------------------------------------------------------------------
keyval *keyval_copy(keyval const *in);
//-------------------------------------------------------------------------------------
void keyval_free (keyval *in );
//-------------------------------------------------------------------------------------
int keyval_matches( keyval const *in, char const *key );


//cci_cli_dictionary
extern void *cci_cli_dictionary_not_found;

typedef struct cci_cli_dictionary{
   keyval **pairs;
   int length;
} cci_cli_dictionary;

//-------------------------------------------------------------------------------------
cci_cli_dictionary *cci_cli_dictionary_new (void );
//-------------------------------------------------------------------------------------
cci_cli_dictionary *cci_cli_dictionary_copy( cci_cli_dictionary *in );
//-------------------------------------------------------------------------------------
void cci_cli_dictionary_free( cci_cli_dictionary *in );
//-------------------------------------------------------------------------------------
void cci_cli_dictionary_add( cci_cli_dictionary *in, char *key , void *value );
//-------------------------------------------------------------------------------------
void *cci_cli_dictionary_find( cci_cli_dictionary const *in , char const *key );
