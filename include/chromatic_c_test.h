/*
 * chromatic_c_test.h
 *
 *  Created on: Aug 21, 2015
 *      Author: wiljoh
 */

#pragma once
//ignore constant char* deprecation
#pragma GCC diagnostic ignored "-Wwrite-strings"

//utils
#include <cci/cci_utils.h>


//types
typedef struct
{
	char text_1[256];
	char text_2[256];
	char text_3[256];

} dfixture;



//services
//------------------------------------------------------------------------------------------
void dict_setup( dfixture* fx , gconstpointer test_data );
void dict_teardown( dfixture* fx , gconstpointer test_data );
void test_compare_equal( dfixture* fx , gconstpointer test_data );
void test_compare_not_equal( dfixture* fx , gconstpointer ignored );
