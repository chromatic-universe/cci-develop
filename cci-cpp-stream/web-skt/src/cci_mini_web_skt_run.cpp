//cci_mini_web_skt_run.cpp   cchromatic universe 2017 william k. johnson

#include <cci_web_skt_stream.hpp>

#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>


using easywsclient::WebSocket;

int main( int argc , char** argv )
{
		    
		    std::unique_ptr<WebSocket> ws(WebSocket::from_url("ws://localhost:7082/cci_mta_trinity-stream"));
		    assert(ws);
		    ws->send("goodbye");
		    ws->send("hello");
		    while (ws->getReadyState() != WebSocket::CLOSED)
		    {
			WebSocket::pointer wsp = &*ws; 
			ws->poll();
			ws->dispatch([wsp](const std::string & message) {
			    printf(">>> %s\n", message.c_str());
			    if (message == "world") { wsp->close(); }
			});
		    }
		    return 0;
}
