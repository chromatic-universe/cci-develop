
#include <iostream>
#include <memory>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <boost/make_shared.hpp>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


#include "CuratorService.h"
#include "EventService.h"


#include <unistd.h>
#include "cci_curator_stream.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace shared;
using namespace cci_cpp_stream;


int main( int argc , char* argv[] )
{

        std::cerr << "cci-curator client(cpp zookeepr manip) 2016\n" \
                     "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n";
        try
        {

            auto cci( std::make_unique<cci_curator_rpc>( "cci-aws-1" ,
                                                         cci_curator_rpc::connection_port ) );
            if( !!cci->valid() )
            {
                std::cerr << "cci-curator initialized........\n";
            }
            sleep( 2 ) ;
        }
        catch ( exception_t& tx )
        {
            std::cerr << "error: " << tx.what() << "\n";
        }

        return 0;
 }


