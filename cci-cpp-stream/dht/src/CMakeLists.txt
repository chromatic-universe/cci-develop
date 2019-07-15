
#version
cmake_minimum_required(VERSION 3.2)
#project
project(dht_stream)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -Qunused-arguments  -DDEBUG -std=c++1z")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic -Qunused-arguments  -DNDEBUG -std=c++1z")

#includes
include_directories( ${dhtStreamSOURCE_DIR}
                     ../include
	                 ../../include
	                 ../../../include
                     $ENV{DEV}/include
                   )
#link location
link_directories( $ENV{DEV}/lib 
                  /usr/lib)
                  

#library
add_library(cci_dht_stream SHARED  cci_dht_stream.cpp)
set_target_properties(cci_dht_stream   PROPERTIES
                                       VERSION 1.0.0
                                       SOVERSION 1) 

#binary
add_executable(cci_mini_dht_run cci_mini_dht_run.cpp)                               
                                   

#link libs
target_link_libraries(cci_mini_dht_run    -lstdc++ 
                                          -lpthread 
                                          -ldl
                                          -lopendht)

#install
install_targets(/lib cci_dht_stream)
install_targets(/bin cci_mini_dht_run)

install (DIRECTORY ../../include/ 
         DESTINATION include)

