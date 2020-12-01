#cmake cci_curl_pp  william k. johnson 2017

#version
cmake_minimum_required(VERSION 3.2)
#project
project(cci_curl_pp)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -DDEBUG -std=c++1z")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic  -DNDEBUG -std=c++1z")

#includes
include_directories( ${cci_curk_ppSOURCE_DIR}
	             ../../include
                     $ENV{DEV}/include
		     $ENV{SOURCE_ROOT}/cci-daemon/include
                   )
#link location
link_directories( $ENV{DEV}/lib
	          $ENV{DEV}/lib64)

#library
add_library(cci_curlpp_stream SHARED cci_curl_stream.cpp)
set_target_properties(cci_curlpp_stream PROPERTIES
                                        VERSION 1.0.0
                                        SOVERSION 1) 


#binary
add_executable(cci_mini_curl_run  cci_mini_curl_run.cpp)                               
                                   

#link libs
target_link_libraries(cci_mini_curl_run -lcurlpp
		                        -lcurl
					-lstdc++
				        -lcci-daemon-core
					 cci_curlpp_stream)

#install
install_targets(/lib cci_curlpp_stream)
install_targets(/bin cci_mini_curl_run)

install (DIRECTORY ../../include/ 
         DESTINATION include)



