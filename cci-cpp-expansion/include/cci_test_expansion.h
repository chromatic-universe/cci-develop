//cci_test_expansion.h   william k. johnson 2016

#pragma once

//gtest
#include <gtest/gtest.h>
//cci
#include <cci_numeric_utils.h>



namespace cci_expansion
{

       //numeric utils test fixture
       class numeric_utils_test_t : public ::testing::Test
       {

            public :

                //ctor
                numeric_utils_test_t() = default;

                //dtor
                ~numeric_utils_test_t() = default;

            protected :

                //attributes
                //integer
                ceu_baby_bits<int,int> b_bits_i;
                //unsigned
                ceu_baby_bits<unsigned,unsigned> b_bits_u;


                virtual void SetUp()
                {
                    //
                }

            public :

                //accessors-inspectors
                ceu_baby_bits<int,int>& integer_bits() { return b_bits_i; }
                ceu_baby_bits<unsigned,unsigned>& unsigned_bits() { return b_bits_u; }

       };

       //-----------------------------------------------------------------
       TEST_F( numeric_utils_test_t  , unique_chars_in_string )
       {
            std::string test_t( "abc d e,,,fg" );
            std::string test_t_2( "abab   ccbtavvp" );
            ascii_bits a_bits;

            //integers
            ////
            //ignore crlf , space , comma , semicolon
            std::vector<int> v_ignore_i{ 0x12,0x13,0x20,0x2C,0x3b };
            for( auto elem : v_ignore_i ) { a_bits.set( elem ); }

            ASSERT_TRUE( integer_bits().is_unique_chars_in_str( test_t , &a_bits ) )
                 << "string of unique characters failed...integer";
            ASSERT_FALSE( integer_bits().is_unique_chars_in_str( test_t_2 , &a_bits ) )
                 << "string of non-unique characters failed...integer";

            //unsigned
            ////
            ASSERT_TRUE( unsigned_bits().is_unique_chars_in_str( test_t , &a_bits ) )
                 << "string of unique characters failed...unsigned";
            ASSERT_FALSE( unsigned_bits().is_unique_chars_in_str( test_t_2 , &a_bits ) )
                 << "string of non-unique characters failed...unsigned";

       }
}


