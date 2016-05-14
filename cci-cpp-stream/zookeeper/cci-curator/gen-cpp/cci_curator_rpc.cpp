//cci_curator_rpc.cpp   william k. johnson 2016

#include "cci_curator_stream.h"

using namespace cci_cpp_stream;

//static initialization
std::string cci_curator_rpc::connection_moniker{ "cci" };
int cci_curator_rpc::connection_port{ 9090 };

//---------------------------------------------------------------------------
std::ostream& operator<< ( std::ostream& ostr , const cci_curator_rpc& ccr )
{
        ostr << "cci_curaotr_rpc:"
             << ccr.end_point()
             << ":"
             << cci_curator_rpc::connection_port
             << "\n";

         return ostr;
}

//----------------------------------------------------------------------------
cci_curator_rpc::cci_curator_rpc( const std::string& end_point ,
                                  int port )
try  :  m_str_end_point( end_point ) ,
        m_port( port ) ,
        m_b_valid { false } ,
        m_b_leader { false  } ,
        m_rpc_socket( new rpc_socket_t( m_str_end_point , m_port ) ) ,
        m_rpc_transport( new rpc_buf_transport_t( m_rpc_socket ) ) ,
        m_protocol( new binary_protocol_t( m_rpc_transport ) ) ,
        m_curator( std::make_unique<curator_service_client>( m_protocol ) ) ,
        m_current_projection( std::make_unique<curator_projection>() ) ,
        m_proj { *m_current_projection.get() }
{

    //open transport
    m_rpc_transport->open();
    //ping
    rpc()->newCuratorProjection(  projection() ,
                                  cci_curator_rpc::connection_moniker );
    rpc()->pingCuratorProjection( projection() );

    m_b_valid = true;

}
catch( exception_t& e )
{
    std::cerr << e.what()
              << "\n";
}

//----------------------------------------------------------------------------
cci_curator_rpc::~cci_curator_rpc()
{
    m_curator->closeCuratorProjection( m_proj );
    m_rpc_transport->close();

    std::cerr << "cci-curator closed....\n";
}







