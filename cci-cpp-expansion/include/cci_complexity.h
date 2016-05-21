
//c++complexity.h william k. johnson 2015


#pragma once

//c++ standard
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <utility>
#include <stack>
#include <set>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <tuple>
#include <memory>
#include <random>
#include <bitset>
#include <stack>
#include <exception>
#include <iterator>

#include <cci_generic.h>

//c rintime
#include <cassert>

namespace cci_expansion
{


            //inline

            //services
            //cci_graph
            class cci_graph
            {
                //stream
                friend std::ostream& operator << ( std::ostream& ostr , const cci_graph& ccg )
                { return ( ostr << "todo" ); }

                public :

                    //ctors
                    cci_graph();
                    explicit cci_graph( const vertices_ptr v , const edges_ptr e );
                    //dtor
                    virtual ~cci_graph();
                    //copy
                    cci_graph( const cci_graph& ccg );
                    //assign
                    const cci_graph& operator= ( const cci_graph& ccg )
                    {
                        //source and destination are the same
                        if( &ccg == this ) { return ( *this ); }
                        //do copy
                        return ( *this );
                    }

                protected :

                    //attributes
                    vertices_ptr m_ptr_vertices;
                    edges_ptr m_ptr_edges;

                    //helpers
                    void add_first_d();
                    void add_second_d();

                private :

                    //attributes
                    std::unique_ptr<graph> m_ptr_graph;

                public :

                    //accessors-inspectors

                    //mutators

                    //helpers
                    //
                    ///vector of keys
                    vertices enum_vertices();
                    ///vector of key values
                    edges enum_edges();
                    ///vertices connected to vertex vx
                    vertices enum_out_vertices( const vertex& vx );
                    ///vector of edges that start from vx
                    edges enum_out_edges( const vertex& vx );
                    ///returns the edge between u and v , null otherwise
                    std::pair<bool,edge> acquire_edge( const std::pair<vertex,vertex> v_duo );

                    //services
                    //
                    ///add vertex
                    void add_vertex( const vertex& v );
                    ///add edge , both directions - replace if exists
                    void add_edge( const edge& e );
                    ///rewmove edge
                    void remove_edge( const edge* e );
                    ///start with edgeless graph and
                    ///add edge between all pairs of vertices
                    void add_all_edges();
                    ///clear all edges
                    void clear_all_edges();
                    ///breadth first search to see if all nodes
                    ///have been visited
                    bool connected_bfs();

                    //immutable


            };
            template <typename A , typename B , typename C>
            class cci_random_manip_t
            {
                //random number hijinks
                typedef A* a_ptr;
                typedef B* b_ptr;
                typedef C* c_ptr;

                friend std::ostream& operator<< ( std::ostream& ostr , const cci_random_manip_t&  crm )
                                                               { return ostr << "cci_random+manip_t"; }

                public:


                    //ctors
                    explicit cci_random_manip_t( A& a , B& b , C& c ) :  m_dw_seed( 0L ) ,
                                                                         m_ptr_collection(  new A( a ) ) ,
                                                                         m_ptr_distribution( new B( b ) ) ,
                                                                         m_ptr_engine( new C( c ) )
                    {}

                    //dtor
                    virtual ~cci_random_manip_t() {};

                protected :

                    //attributes
                    int m_dw_seed;


                private :

                    //attributes
                    std::unique_ptr<A> m_ptr_collection;//container
                    std::unique_ptr<B> m_ptr_distribution;//value to numeric
                    std::unique_ptr<C> m_ptr_engine;//random algorithms

                    //no copy
                    cci_random_manip_t( const cci_random_manip_t& crm );
                    //no assign
                    cci_random_manip_t& operator= ( const cci_random_manip_t& crm );

                public :

                   //accessors-inspectors
                   a_ptr collection() { return( m_ptr_collection.get() ); }
                   b_ptr distribution() { return( m_ptr_distribution.get() ); }
                   c_ptr engine() { return( m_ptr_engine.get() ); }

                   //mutators


                   //services
                   virtual int acquire_seed()  { return ( 0 ); }
                   //-------------------------------------------------------------
                   virtual A shuffle_t( const A& collection ,
                                        C& engine )
                   {
                        //caller has to seed engine
                        A shuffled { collection };

                        std::shuffle( shuffled.begin() , //range begin
                                      shuffled.end() ,   //range end
                                      engine );          //randomness

                        return ( shuffled );
                   }
                   //-------------------------------------------------------------
                   virtual void shuffle_t()
                   {
                       std::shuffle(  collection()->begin() , //range begin
                                      collection()->end() ,   //range end
                                      *engine() );             //randomness
                   }
                   //-------------------------------------------------------------
                  void  gen_random_init_t( A& collection ,
                                           B& distribution ,
                                           C& engine
                                         )
                  {
                        //caller has to seed engine
                        //
                        //number of generated elements
                        //is sizeof collection
                        for( auto& elem : collection )
                        {
                            elem = distribution( engine  );
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
                            elem = (*distribution() ) ( engine() );
                        }
                  }

            };


}

