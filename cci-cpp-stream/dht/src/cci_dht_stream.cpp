//cci_dht_stream.cpp  chromatic universe 2019  william k. johnson

//contrib
#include <cci_dht_stream.h>


using namespace cpp_real_stream;

//immutable


unsigned cci_dht_stream::dht_port = 13003UL;


//-------------------------------------------------------------------------------------
cci_dht_stream::cci_dht_stream() :  m_bootstrap { "nil" } ,
                                    m_dht_node ( std::make_shared<dht_runner>() ) ,
                                    m_port { cci_dht_stream::dht_port }
{
}

//-------------------------------------------------------------------------------------
cci_dht_stream::cci_dht_stream( const std::string& bootstrap ,
                                unsigned port )
try : m_bootstrap { bootstrap }  ,
      m_dht_node( std::make_shared<dht_runner>() ) ,
      m_port { port }
{
}
catch( const dht::DhtException& dht_err )
{
        std::cerr << "...opendht library exception..."
                  << dht_err.what()
                  << "\n";

}
catch( const std::exception& err )
{
        std::cerr << err.what()
                      << "\n";
}

//-------------------------------------------------------------------------------------
cci_dht_stream::~cci_dht_stream()
{
        if( m_dht_node ) { m_dht_node->join(); }
}


