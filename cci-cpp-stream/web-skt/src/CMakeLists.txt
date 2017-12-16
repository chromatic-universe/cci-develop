#cmake cci_curl_pp  william k. johnson 2017

#version
cmake_minimum_required(VERSION 3.2)
#project
project(web-skt)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -DDEBUG -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic  -DNDEBUG -std=c++11")

#includes
include_directories( ${web-sktSOURCE_DIR}
	             ../../include
                     $ENV{DEV}/include
                   )
#link location
link_directories( $ENV{DEV}/lib)

#library
add_library(cci_web_skt_stream SHARED cci_web_skt_stream.cpp)
set_target_properties(cci_web_skt_stream PROPERTIES
                                  VERSION 1.0.0
                                  SOVERSION 1) 


#binary
add_executable(cci_mini_web_skt_run  cci_mini_web_skt_run.cpp)                               
                                   

#link libs
target_link_libraries(cci_mini_web_skt_run  cci_web_skt_stream)

#install
install_targets(/lib cci_web_skt_stream)
install_targets(/bin cci_mini_web_skt_run)

install (DIRECTORY ../../include/ 
         DESTINATION include)



