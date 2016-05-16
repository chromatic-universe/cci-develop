//
#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-private-field"

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <iomanip>
#include <cctype>
#include <cstdio>
#include <map>

namespace walk_a_baby
{
        //forward declarations
        class walk_a_baby_lex;

        //types
        typedef walk_a_baby_lex*   walk_a_baby_lex_ptr;
        typedef std::istream*       istr_ptr;
        typedef std::ifstream*      ifstr_ptr;

        //enumerations
        enum class token_type : int
        {
            tok_eof = -1 ,
            // commands
            tok_func_def = -2 ,
            tok_extern = -3 ,
            // primary
            tok_identifier = -4 ,
            tok_numeric = -5 ,
            //conditional
            tok_if = -6 ,
            tok_then = -7 ,
            tok_else = -8 ,
            tok_for = -9 ,
            tok_in = -10 ,
            tok_binary = -11 ,
            tok_unary = -12
        };

        enum class stream_type : unsigned long
        {
            st_file_stream ,
            st_string_stream ,
            st_stream_buf
        };


        //classes
        class walk_a_baby_lex
        {
             friend std::ostream & operator<< ( std::ostream &ostr , const walk_a_baby_lex& wabl );

             public :

                    //ctor
                    explicit walk_a_baby_lex();

                    //dtor
                    virtual ~walk_a_baby_lex();

             protected :

                     //attributes

                     //helpers
                     static void stream_factory( const stream_type st );

             private :

                    //attributes
                    static std::unique_ptr<std::ifstream> m_ptr_ifstr;

                    //no copy
                    walk_a_baby_lex( const walk_a_baby_lex& wabl );
                    //no assign
                    const walk_a_baby_lex&  operator= ( const walk_a_baby_lex& wabl );
                    //repr-todo


             public :

                   static ifstr_ptr stream() { return ( m_ptr_ifstr.get() ); }

                   //services
                   static int stream_p();
                   static void open_stream( const std::string& filename );
                   static void open_stream();
                   static int acquire_token();

                   //immutable
                   static int m_numeric_val;
                   static std::string m_string_ident_val;
                   static std::string function_prefix;
                   static std::string extern_prefix;
                   static std::string if_prefix;
                   static std::string then_prefix;
                   static std::string else_prefix;
                   static std::string for_prefix;
                   static std::string in_prefix;
                   static std::string bin_prefix;
                   static std::string unary_prefix;
        };
}

