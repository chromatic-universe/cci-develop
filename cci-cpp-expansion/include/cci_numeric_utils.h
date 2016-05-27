//cci_numeric_utils.h william k. johnson 2015
    pragma once

//c++ standard
#include <random>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <exception>
#include <vector>
#include <bitset>
#include <map>
#include <utility>
#include <stack>
#include <bitset>

//c runtime
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <map>


//chromatic
#include <cci_generic.h>

namespace cci_expansion
{


        //forward declarations

        //enumerations


        //constants
        #define ascii_chars 256

        //classes
        //--------------------------------------------------------------------
        template<typename A , typename B>
        class ceu_baby_bits
        {
            //bit and stream bits manip
            public :

                //ctor
                ceu_baby_bits() {}
                //dtor
                ~ceu_baby_bits() {}

            protected :

                //attributes

            private :

                //attributes

            public :


                //services
                //------------------------------------------------------------
                static void v_to_ascii_bits( const std::vector<A>& v ,
                                             ascii_bits& bits )
                {

                     std::for_each( v.begin() ,
                                    v.end()  ,
                                    [&bits] ( int elem )
                                    {
                                         if( elem > ascii_chars )
                                         {
                                            throw std::out_of_range( "value exceeds ascii extended enum..." );
                                         }
                                         bits.set( elem );
                                    }
                                  );

                }
                //------------------------------------------------------------
                static A bin_str_to_num( const std::string& bin_str )
                {

                    A dw { 0 };

                    try
                    {
                        //upgrade
                        dw = std::bitset<sizeof( A ) * 8> ( bin_str ).to_ulong();
                    }
                    catch( const std::invalid_argument& ia )
                    {
                        std::cerr << "invalid argument: " << ia.what() << std::endl;
                    }

                    return ( dw );
                }
                //------------------------------------------------------------
                static std::string num_to_bin_str( A dw )
                {
                    //template param to binary string repr
                    std::string str;
                    try
                    {
                         str = std::bitset<std::numeric_limits<A>::digits> ( dw ).to_string() ;
                    }
                    catch ( const std::invalid_argument& ia )
                    {
                         std::cerr << "invalid argument: " << ia.what() << std::endl;
                    }
                    return ( str );
                }
                //------------------------------------------------------------
                static ascii_bits chars_in_str( const std::string& str ,
                                                char_count_ptr cc = nullptr
                                              )
                {
                    //todo - overload this for streams
                    //char_count map<char,unsigned long>
                    assert( cc );

                    //zero container for increment , map of chars to count of chars
                    std::for_each(  cc->begin() ,
                                    cc->end() ,
                                    [] ( std::pair<const char,unsigned long>& elem )
                                    {
                                       elem.second = 0L;
                                    }
                                  );
                    //hash for ascii chars , initialized to false
                    ascii_bits a_bits;
                    a_bits.reset();

                    for( auto elem : str )
                    {
                                     //duplicate char , this is here
                                     //so we don't do a find and increment
                                     //for values we know aren't there
                                     if( a_bits.test( elem ) == true )
                                     {
                                        auto ch_iter = cc->find( (int) elem );
                                        if( ch_iter != cc->end() )
                                        {
                                             ch_iter->second++;
                                        }
                                     }
                                     else
                                     {
                                        //set initial instance
                                        a_bits.set( elem );
                                        int val = elem;
                                        cc->insert( std::make_pair<char,unsigned long>( val , 1L ) );
                                     }
                    }
                    //return the bitset if caller wants
                    //to use it , such as finding out quickly
                    //what chars are not in the string
                    return ( a_bits );

                }
                //------------------------------------------------------------
                static bool is_unique_chars_in_str( const std::string& str ,
                                                    ascii_bits_ptr exclude_bits )
                {
                    //are there any unique chars
                    bool b_ret { true };
                    ascii_bits a_bits;
                    //exclude these bits
                    assert( exclude_bits );

                    for( auto elem : str )
                    {
                        if( ( a_bits.test( elem ) == true ) &&
                            ( exclude_bits->test( elem ) == false ) )
                        {
                            b_ret = false;
                            break;
                        }
                        a_bits.set( elem );
                    }

                    return ( b_ret );
                }

                //--------------------------------------------------------------------------------------
                static std::string reverse_words( const std::string& words , const std::string& delimiter  )
                {
                    //use a stack to reverse words in a string
                    //todo = overload this for streams
                    std::ostringstream ostr;
                    std::unique_ptr<std::stack<std::string> > word_stack( new std::stack<std::string> );

                    safe_tokenize_t<std::stack<std::string>>( *word_stack.get() , words.c_str() , delimiter.c_str() );

                    do
                    {
                      ostr << word_stack->top() << delimiter;
                      word_stack->pop();
                    }
                    while( word_stack->empty() == false );

                    return ( ostr.str() );
                }
        };
        //types( integral type && base )
        using baby_bits = ceu_baby_bits<int,int>;


        //generic
        //---------------------------------------------------------------------s
        template <typename collection , typename distrib , typename engine >
        class ceu_random_manip_t
        {
            //random number hijinks
            using a_ptr = collection*;
            using b_ptr = distrib*;
            using c_ptr = engine*;

            friend std::ostream& operator<< ( std::ostream& ostr , const ceu_random_manip_t&  crm )
                                                           { return ostr << "ceu_random+manip_t"; }

            public:


                //ctors
                explicit ceu_random_manip_t( collection& a , distrib& b , engine& c ) :  m_dw_seed( 0L ) ,
                                                                     m_ptr_collection(  new collection( a ) ) ,
                                                                     m_ptr_distribution( new distrib( b ) ) ,
                                                                     m_ptr_engine( new engine( c ) )
                {}

                //dtor
                virtual ~ceu_random_manip_t() {};

            protected :

                //attributes
                int m_dw_seed;


            private :

                //attributes
                std::unique_ptr<collection> m_ptr_collection;//container
                std::unique_ptr<distrib> m_ptr_distribution;//value to numeric
                std::unique_ptr<engine> m_ptr_engine;//random algorithms

                //no copy
                ceu_random_manip_t( const ceu_random_manip_t& crm );
                //no assign
                ceu_random_manip_t& operator= ( const ceu_random_manip_t& crm );

            public :

               //accessors-inspectors
               a_ptr collection_() { return( m_ptr_collection.get() ); }
               b_ptr distribution() { return( m_ptr_distribution.get() ); }
               c_ptr engine_() { return( m_ptr_engine.get() ); }

               //mutators


               //services
               virtual int acquire_seed()  { return ( 0 ); }
               //-------------------------------------------------------------
               virtual collection shuffle_t( const collection& coll ,
                                             engine& eng )
               {
                    //caller has to seed engine
                    collection shuffled { coll };

                    std::shuffle( shuffled.begin() , //range begin
                                  shuffled.end() ,   //range end
                                  eng );          //randomness

                    return ( shuffled );
               }
               //-------------------------------------------------------------
               virtual void shuffle_t()
               {
                   std::shuffle(  collection_()->begin() , //range begin
                                  collection_()->end() ,   //range end
                                  *engine() );             //randomness
               }
               //-------------------------------------------------------------
              void  gen_random_init_t( collection& coll ,
                                       distrib& distribution ,
                                       engine& eng
                                     )
              {
                    //caller has to seed engine
                    //
                    //number of generated elements
                    //is sizeof collection
                    for( auto& elem : coll )
                    {
                        elem = distribution( eng  );
                    }

              }
               //-------------------------------------------------------------
              void  gen_random_init_t()
              {

                    //caller has to seed engine
                    //
                    //number of generated elements
                    //is sizeof collection
                    for( auto& elem : collection() )
                    {
                        elem = (*distribution() ) ( engine_() );
                    }
              }

        };


}
namespace cexp = cci_expansion;

