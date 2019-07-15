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
//contrib
#include <opendht.h>


namespace cpp_real_stream
{

                //forward decalrations


                //-------------------------------------------------------------------------------------------------------------------
                class cci_dht_stream
                {

                            public :

                                //ctors
                                cci_dht_stream();
                                //explicit cci_dht_stream();


                                //dtor
                                ~cci_dht_stream() = default;


                                //no copy
                                cci_dht_stream( const cci_dht_stream& ) = delete;
                                cci_dht_stream( const cci_dht_stream&& ) = delete;
                                //no assign
                                cci_dht_stream& operator= ( const cci_dht_stream&  ) = delete;
                                cci_dht_stream& operator= ( const cci_dht_stream&&  ) = delete;


                            private :

                                //attributes


                            protected :


                                //sttrributes

                                //helpers



                            public :


                                //accessors-inspectiors

                                //services

                };



}


