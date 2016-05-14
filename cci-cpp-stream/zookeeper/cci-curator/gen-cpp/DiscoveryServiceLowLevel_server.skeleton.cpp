// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "DiscoveryServiceLowLevel.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::shared;

class DiscoveryServiceLowLevelHandler : virtual public DiscoveryServiceLowLevelIf {
 public:
  DiscoveryServiceLowLevelHandler() {
    // Your initialization goes here
  }

  void queryForInstance(DiscoveryInstance& _return, const CuratorProjection& projection, const DiscoveryProjection& discoveryProjection, const std::string& name, const std::string& id) {
    // Your implementation goes here
    printf("queryForInstance\n");
  }

  void queryForInstances(std::vector<DiscoveryInstance> & _return, const CuratorProjection& projection, const DiscoveryProjection& discoveryProjection, const std::string& name) {
    // Your implementation goes here
    printf("queryForInstances\n");
  }

  void queryForNames(std::vector<std::string> & _return, const CuratorProjection& projection, const DiscoveryProjection& discoveryProjection) {
    // Your implementation goes here
    printf("queryForNames\n");
  }

  void registerInstance(const CuratorProjection& projection, const DiscoveryProjection& discoveryProjection, const DiscoveryInstance& instance) {
    // Your implementation goes here
    printf("registerInstance\n");
  }

  void unregisterInstance(const CuratorProjection& projection, const DiscoveryProjection& discoveryProjection, const DiscoveryInstance& instance) {
    // Your implementation goes here
    printf("unregisterInstance\n");
  }

  void updateInstance(const CuratorProjection& projection, const DiscoveryProjection& discoveryProjection, const DiscoveryInstance& instance) {
    // Your implementation goes here
    printf("updateInstance\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<DiscoveryServiceLowLevelHandler> handler(new DiscoveryServiceLowLevelHandler());
  shared_ptr<TProcessor> processor(new DiscoveryServiceLowLevelProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

