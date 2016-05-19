//cci_generic.h william k. johnson 2016

//
//header for non-application specific tenplates
//using C++11
#pragma once

#ifndef _GENERIC_H
#define _GENERIC_H

//c++ standard
#include <stdexcept>
#include <exception>
#include <system_error>
#include <new>
#include <ios>
#include <future>
#include <typeinfo>
#include <iostream>
#include <exception>
#include <system_error>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <chrono>
#include <tuple>
#include <functional>

//generic interfaces
namespace cci_expansion
{


                 //forward declarations
                class cci_graph;
                template <typename A , typename B , typename C>
                class cci_random_manip_t;

                //enumerations


                //constants
                #define ascii_chars 256

                //immutable
                static const unsigned long char_set_sz = 256;//ascii
                static const  std::string space = " ";//ascii



                //user types
                using   char_count = std::map<char,unsigned long>;
                using   char_count_ptr = char_count*;
                using   v_bool =  std::vector<bool>;
                using   v_bool_ptr = v_bool*;
                using   ascii_bits = std::bitset<ascii_chars>;
                using   edge = std::tuple<std::string,std::string>;
                using   edges = std::vector<edge>;
                using   ptr_edge = edge*;
                using   vertex =  std::string;
                using   ptr_vertex =  vertex*;
                using   vertices = std::vector<vertex>;
                using   vertices_ptr = vertices*;
                using   edges_ptr = edges*;
                using   graph = std::map<vertex,std::map<vertex,edge>>;
                using   graph_ptr = cci_expansion::graph*;
                using   cci_graph_ptr = cci_graph*;
                using   char_count = std::map<char,unsigned long>;
                using   char_count_ptr = char_count*;
                using   v_bool = std::vector<bool>;
                using   v_bool_ptr = v_bool*;
                using   ascii_bits = std::bitset<ascii_chars>;
                using   randon_default_manip =  cci_random_manip_t<std::vector<int> ,
                                                std::uniform_int_distribution<int> ,
                                                std::default_random_engine>;
                using   random_float_manip =    cci_random_manip_t<std::vector<double> ,
                                                std::uniform_real_distribution<double> ,
                                                std::default_random_engine>;


                //inline
                //cartesian product
                template<typename range_0 , typename range_1 , typename output_iterator>
                void cartesian_product( range_0 const &r0 ,  range_1 const &r1 , output_iterator out )
                {
                    using std::begin; using std::end;

                    for ( auto i = begin( r0 ); i != end ( r0 ); ++i )
                    {
                        for ( auto j = begin( r1 ); j != end( r1 ); ++j )
                        {
                            if( *i == *j ) { continue; }
                            *out++ = std::make_tuple( *i , *j );
                        }
                    }
                }

                ///size of array - compile time
                template<typename T , std::size_t N>
                constexpr std::size_t array_size( T (&) [N] ) noexcept
                {
                    //deduction of return value type also deduces
                    //numer of elements
                    return ( N );
                }

                //lists , deques , vectors
                template <typename A , typename B>
                inline int add_element_t(A const& collection , B const& element)
                {
                    collection.push_back(element);

                    return (collection.size());
                }

                //lists , deques , vectors , std::strings
                template <typename A >
                inline int get_element_count_t( A& collection )
                {
                    return (collection.size());
                }


                //all containers
                template <typename A>
                inline void clear_elements_t( A& collection )
                {
                    collection.clear();
                }

                //lists , deques , vectors
                template <typename A>
                inline int safe_tokenize_t( A& collection , const char* szStr,
                                                           const char* delimiters = " " )
                {
                    std::string  str(szStr);

                    // Skip delimiters at beginning , i.e leading whitespace
                    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

                    // Find first "non-delimiter".
                    std::string::size_type pos  = str.find_first_of(delimiters, lastPos);

                    while (std::string::npos != pos || std::string::npos != lastPos)
                    {
                        std::string fstr;

                        fstr = str.substr(lastPos, pos - lastPos);

                        // Found a token, add it to the vector.
                        collection.push_back( fstr );

                        // Skip delimiters.  Note the "not_of"
                        lastPos = str.find_first_not_of(delimiters, pos);

                        // Find next "non-delimiter"
                        pos = str.find_first_of(delimiters, lastPos);
                    }

                    return (collection.size());
                };

                //lists , deques , vectors
                template <typename A , typename B>
                inline void  get_element_at_t( A const& collection , B const& element , const int idx )
                {
                    try
                    {
                        element = collection.at(idx);

                    }
                    catch(std::out_of_range& e)
                    {
                        //
                    }
                }

                //return map value for key , maps
                template <typename A , typename B>
                inline A get_map_element_at_t( A const& key , B const& map )
                {

                    A value;
                    typename B::const_iterator pos;

                    for( pos = map.begin(); pos != map.end(); ++pos )
                    {
                        if( pos->first == key )
                        {
                            value = pos->second;

                            break;
                        }
                    }

                    return ( value );

                }

                //stream key pairs of map/multimap
                template <typename A , typename B>
                inline void stream_map_elements_t( A const& map , B& stream ,
                                                   const std::string& sep = " " ,
                                                   const std::string& terminator = "\n")
                {

                    typename A::const_iterator pos;

                    for( pos = map.begin(); pos != map.end(); ++pos )
                    {
                        stream << pos->first << sep << pos->second << terminator ;
                    }

                    stream << std::ends;
                }

                template <typename A >
                inline A return_type_spec( A const& typ )
                {

                    return  typ;

                }

                template <typename T1, typename T2>
                    std::ostream& operator << ( std::ostream& strm, const std::pair<T1,T2>& p )
                    {
                        return strm << "[" << p.first << "," << p.second << "]";
                    }

                template <int i, int t_size, typename tpl>
                    struct iterate_over_tuple_impl
                        : public iterate_over_tuple_impl<i + 1, t_size, tpl>
                    {
                            template <typename Function>
                            void operator () (Function& f, tpl& t)
                            {
                                f( std::get<i>( t ) );
                                iterate_over_tuple_impl<i + 1, t_size, tpl>::operator () ( f , t );
                            }
                    };

                    template <int I, typename Tuple>
                    struct iterate_over_tuple_impl<I, I, Tuple> {
                        template <typename Function>
                            void operator () (Function& f, Tuple& t) {}
                    };


                    template <typename Function, typename... Args>
                    void iterate_over_tuple(Function& f, std::tuple<Args...>& t)
                    {
                        iterate_over_tuple_impl<0, sizeof...(Args), std::tuple<Args...>>() (f, t);
                    }

                    template <int idx, int max, typename... Args>
                    struct print_tuple
                    {
                        static void print ( std::ostream& strm , const std::tuple<Args...>& t )
                        {
                            strm << std::get<idx>(t) << (idx + 1== max ? "" : ",");
                            print_tuple<idx + 1 , max , Args...>::print ( strm , t );
                        }
                    };

                    template <int max, typename... Args>
                    struct print_tuple<max , max ,Args...>
                    {
                        static void print (std::ostream& strm, const std::tuple<Args...>& t)
                        {
                        }
                    };

                    template <typename... Args>
                    std::ostream& operator << ( std::ostream& strm,
                                                const std::tuple<Args...>& t )
                    {
                        strm << "[";
                        print_tuple<0,sizeof...(Args),Args...>::print( strm , t );

                        return strm << "]";
                    }

                    template <typename V, typename R>
                    std::ostream& operator << ( std::ostream& s, const std::chrono::duration<V,R>& d )
                    {
                        s << "[" << d.count() << " of " << R::num << "/"
                        << R::den << "]";

                        return s;
                    }

                    template <typename C>
                    void print_clock_data()
                    {

                            std::cout << "- precision: ";
                            // if time unit is less or equal one millisecond
                            typedef typename C::period P;
                            // type of time unit
                            if ( std::ratio_less_equal<P,std::milli>::value )
                            {
                                // convert to and print as milliseconds
                                typedef typename std::ratio_multiply<P,std::kilo>::type TT;
                                std::cout << std::fixed << double(TT::num)/TT::den << " milliseconds" <<  std::endl;
                            }
                            else
                            {
                                // print as seconds
                                std::cout << std::fixed << double(P::num)/P::den << " seconds" << std::endl;
                            }
                            std::cout << "- is_steady: " << std::boolalpha << C::is_steady << std::endl;

                    }
}
#endif //_GENERIC_H
