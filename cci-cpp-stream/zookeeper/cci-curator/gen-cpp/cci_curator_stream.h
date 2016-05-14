#include "CuratorService.h"
#include "EventService.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TBufferTransports.h>
#include <memory>
#include <sstream>

#include <unistd.h>
namespace cci_cpp_stream
{

            //forward declarations
            class cci_curator_rpc;

            //aliases
            using curator_service_client = shared::CuratorServiceClient;
            using curator_projection = shared::CuratorProjection;
            using cci_curator_ptr = cci_curator_rpc*;
            using rpc_projection_ptr = curator_projection*;
            using rpc_curator_ptr = curator_service_client*;
            using binary_protocol_t = apache::thrift::protocol::TBinaryProtocol;
            using rpc_socket_t = apache::thrift::transport::TSocket;
            using exception_t = apache::thrift::TException;
            using rpc_transport_t = apache::thrift::transport::TTransport;
            using rpc_buf_transport_t = apache::thrift::transport::TBufferedTransport;
            using binary_protocol_ptr = binary_protocol_t*;

            //enumerations


            //services
            class cci_curator_rpc
            {
                public :

                    //repr
                    friend std::ostream& operator<< ( std::ostream& ostr , const cci_curator_rpc& ccr );

                    //ctor
                    explicit cci_curator_rpc( const std::string& end_point , int port = 9090 );
                    //no copy
                    cci_curator_rpc( const cci_curator_rpc& ccr ) = delete;
                    //no assign
                    const cci_curator_rpc& operator= ( const cci_curator_rpc& ccr ) = delete;

                    //use unary bool compare
                    bool operator!() const { return !m_b_valid; }
                    //disable bitwise compare
                    friend bool operator== ( const cci_curator_rpc &a , const cci_curator_rpc &b ) = delete;
                    friend bool operator!= ( const cci_curator_rpc &a , const cci_curator_rpc &b ) = delete;

                    //dtor
                    virtual ~cci_curator_rpc();

                private :

                    //attributes
                    std::string                             m_str_end_point;
                    int32_t                                 m_port;
                    bool                                    m_b_valid;
                    bool                                    m_b_leader;

                protected :

                     //attributes
                     //
                     //thrift interfaces
                     boost::shared_ptr<rpc_transport_t>     m_rpc_socket;
                     boost::shared_ptr<rpc_transport_t>     m_rpc_transport;
                     boost::shared_ptr<binary_protocol_t>   m_protocol;

                private :

                     //attributes
                     //
                     //we put these down here to accentuate
                     //the creation order dependencies
                     //
                     //composed rpc object
                     std::unique_ptr<curator_service_client> m_curator;
                     //projection=zookeeper instance
                     std::unique_ptr<curator_projection>     m_current_projection;
                     //stack local for thrift reference semantics
                     curator_projection                      m_proj;

                public :

                     //accessors-inspectors }
                     constexpr bool valid() const noexcept { return m_b_valid; }
                     constexpr bool leader() const noexcept { return m_b_leader; }
                     std::string end_point() const noexcept { return m_str_end_point; }
                     rpc_curator_ptr rpc() { return m_curator.get(); }
                     curator_projection& projection() { return m_proj; }

                     //immutable
                     static std::string connection_moniker;
                     static int connection_port;

                     //services

            };


}

