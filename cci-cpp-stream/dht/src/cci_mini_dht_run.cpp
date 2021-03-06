#include <vector>


#include <cci_dht_stream.h>


int main()
{
        dht::DhtRunner node;

        // Launch a dht node on a new thread, using a
        // generated RSA key pair, and listen on port 4222.
        node.run(4222, dht::crypto::generateIdentity(), true);

        // Join the network through any running node,
        // here using a known bootstrap node.
        node.bootstrap("50.122.108.135", "13003");
        std::cerr << node.getNodesStats( AF_INET ).toString() << "\n";
        if( ! node.isRunning() )
        {
            std::cerr << "...not....\n";
            _exit( 1 );
        }


        // put some data on the dht
        std::vector<uint8_t> some_data(5, 10);
        node.put("unique_key", some_data);

        // put some data on the dht, signed with our generated private key
        node.putSigned("unique_key_42", some_data);

        // get data from the dht
        node.get("other_unique_key", [](const std::vector<std::shared_ptr<dht::Value>>& values) {
            // Callback called when values are found
            for (const auto& value : values)
                std::cout << "Found value: " << *value << std::endl;
            return true; // return false to stop the search
        });

        // wait for dht threads to end
        node.join();
        return 0;
}

