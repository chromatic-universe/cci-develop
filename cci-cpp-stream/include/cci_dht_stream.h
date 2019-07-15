//cci_dht_stream.h   chromatic universe 2019  william k. johnson



#pragma once

//c++ standard
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>

//contrib
#include <opendht.h>


namespace cpp_real_stream
{

                //forward decalrations


                //aliases
                using dht_runner = dht::DhtRunner;
                using dht_runner_t = dht_runner*;


                //-------------------------------------------------------------------------------------------------------------------
                class cci_dht_stream
                {

                            public :

                                //ctors
                                explicit cci_dht_stream( const std::string& bootstrap =  "hil" ,
                                                         unsigned port = dht_port );
                                cci_dht_stream();


                                //dtor
                                ~cci_dht_stream();


                                //no copy
                                cci_dht_stream( const cci_dht_stream& ) = delete;
                                cci_dht_stream( const cci_dht_stream&& ) = delete;
                                //no assign
                                cci_dht_stream& operator= ( const cci_dht_stream&  ) = delete;
                                cci_dht_stream& operator= ( const cci_dht_stream&&  ) = delete;


                            private :

                                //attributes
                                std::string                       m_bootstrap;
                                std::shared_ptr<dht_runner>       m_dht_node;
                                unsigned                          m_port;


                            protected :


                                //sttrributes

                                //helpers



                            public :


                                //accessors-inspectiors
                                dht_runner_t node() { return m_dht_node.get(); }
                                unsigned port() const noexcept { return m_port; }
                                std::string bootstrap() const noexcept { return m_bootstrap; }
                                //mutators
                                void port( const unsigned& prt ) { m_port = prt; }
                                void bootstrap( const std::string& strap ) { m_bootstrap = strap; }


                                //services


                            //immutable
                            static unsigned dht_port;

                };



}


