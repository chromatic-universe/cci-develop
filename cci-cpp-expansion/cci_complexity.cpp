//c++complexity.cpp william k. johnson 2015


#include <cci_complexity.h>

using namespace cci_expansion;

std::ostream& operator<< ( std::ostream& ostr , const edge e )
{
               ostr << "edge( "
                    << std::get<0>( e )
                    << " , "
                    << std::get<1>( e )
                    << " )";
               return ( ostr );
}

cci_graph::cci_graph( const vertices_ptr v , const edges_ptr e )  :  m_ptr_vertices { v } ,
                                                                     m_ptr_edges { e } ,
                                                                     m_ptr_graph( new cci_expansion::graph )
{
    //
}

//------------------------------------------------------------------------
cci_graph::cci_graph()
{
    //
}

//------------------------------------------------------------------------
cci_graph::cci_graph( const cci_graph& ccg )
{
    //
}

//------------------------------------------------------------------------
cci_graph::~cci_graph()
{
    //
}

//------------------------------------------------------------------------
void cci_graph::add_first_d()
{
   //vector of vertices
   for( auto elem : *m_ptr_vertices )
   {
       //dictionary data
       std::map<vertex,edge> m;
       std::pair<vertex , std::map<vertex,edge>> pr( elem , m );
       //vertex key and dictionary data
       m_ptr_graph->insert(  pr );
   }

}

//-------------------------------------------------------------------------
void cci_graph::add_second_d()
{

    //vector of edges
    //add or replace , we don't need returned iterator
    for( auto elem : *m_ptr_edges )
    {
          //undirected edge , symmetrical
          ( *m_ptr_graph.get() )[std::get<0>( elem )][std::get<1>( elem )] = elem;
                                 std::cout << "edge: " << "["  << std::get<0>( elem ) << "]"
                                           << "["  << std::get<1>( elem ) << "]"
                                           << "\n";
    }
}

//--------------------------------------------------------------------------
///vector of keys
vertices cci_graph::enum_vertices()
{
    vertices v;
    for( auto elem : *m_ptr_graph.get() ) { v.push_back( elem.first ); }

    return ( v );
}

//--------------------------------------------------------------------------
///vector of key values
edges cci_graph::enum_edges()
{
    //unique , use set indirection
    std::set<edge> b_set;
    std::vector<edge> v;
    for( auto elem : *m_ptr_graph.get() )
    {
       for( auto j_elem : elem.second ) { b_set.insert( j_elem.second );  }
    }
    v.assign( b_set.begin() , b_set.end() );
    //

    return ( v );
}

//------------------------------------------------------------------------
///vector of vertices connected to vertex vx
vertices cci_graph::enum_out_vertices( const vertex& vx )
{
       vertices v;
       auto idx = m_ptr_graph.get()->find( vx );
       if ( idx != m_ptr_graph.get()->end() )
       {
               v.push_back( idx->first );
       }

       return ( v );
}

//------------------------------------------------------------------------
///vector of edges that start from vx
edges cci_graph::enum_out_edges( const vertex& vx )
{
       std::vector<edge> v;
       auto idx = m_ptr_graph.get()->find( vx );
       if ( idx != m_ptr_graph.get()->end() )
       {
          for( auto elem : idx->second ) { v.push_back( elem.second ); }
       }

       return ( v );

}
//------------------------------------------------------------------------
///edge between vertex pair
std::pair<bool,edge> cci_graph::acquire_edge( const std::pair<vertex,vertex> v_duo )
{
       std::pair<bool,edge> pr;
       pr.first = false;

       auto idx = m_ptr_graph->find( v_duo.first );
       if(  idx != m_ptr_graph->end() )
       {
             auto jdx = *idx->second.find( v_duo.second );
             if( jdx != *idx->second.end() )
             {
                 pr.first = true;
                 pr.second = jdx.second;
             }
       }

       return ( pr );
}

//------------------------------------------------------------------------
//add vertex to graph , noop if exists
void cci_graph::add_vertex( const vertex&  v )
{
      auto vx = m_ptr_graph->find( v );
      if( vx  == m_ptr_graph->end() )
      {
        //no vertex exists , add one
        std::map<vertex,edge> m;
        std::pair<vertex , std::map<vertex,edge>> pr( v , m );
        //vertex key and dictionary data
        m_ptr_graph->insert(  pr );
      }
      //else nothing
}
//------------------------------------------------------------------------
//remove edge
void cci_graph::remove_edge( const edge* e )
{
      //remove all references to edge from graph
}

//------------------------------------------------------------------------
//add edge to graph both directions - replace if exists
void cci_graph::add_edge( const edge& e )
{
      auto vx = m_ptr_graph->find( std::get<0>( e ) );
      if( vx != m_ptr_graph->end() )
      {
           //first direction
           //vertex exists
           auto jvx = *vx->second.find( std::get<1>( e ) );
           if( jvx != *vx->second.end() )
           {
              //no edge . add one
              jvx.second = e;
           }
      }
      //second direction
      //edge ex{ std::get<1>( e ) , std::get<0>( e ) };
      //add_edge( ex );

}

//------------------------------------------------------------------------
///start with edgeless graph and add edge between all pairs of vertices
void cci_graph::add_all_edges()
{
    //clear graph edges
    edge e;

    std::vector<std::string> a;
    std::vector<std::string> b;

    std::vector<std::tuple<std::string , std::string>> items;
    cartesian_product( a , b, back_inserter( items ) );

    for ( auto &&tup : items )
    {
        std::cout << "("
                  << std::get<0>( tup )
                  << ","
                  << std::get<1>( tup )
                  << ")";
    }
}

//------------------------------------------------------------------------
///start with edgeless graph and add edge between all pairs of vertices
void cci_graph::clear_all_edges()
{
    //
}

//------------------------------------------------------------------------
///breadth first search to see if all nodes have been visited
bool cci_graph::connected_bfs()
{
    return ( true );
}

















