
#version
cmake_minimum_required(VERSION 3.2)
#project
project(stream_event)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -Qunused-arguments  -DDEBUG -std=c++1z")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic -Qunused-arguments  -DNDEBUG -std=c++1z")

#includes
include_directories( ${stream_eventSOURCE_DIR}
                     ../include
	                 ../../include
	                 ../../../include
                     $ENV{DEV}/include
                     $ENV{DEV}/chilkat-9.5.0-x86_64-linux-gcc/include
		             $ENV{DEV}/chilkat-9.5.0-armv7a-hardfp-linux/include
		             $ENV{DEV}/chilkat-9.5.0-armv7l-linux/include
          	         $ENV{DEV}/chilkat-9.5.0-aarch64-linux/include
                     $ENV{SOURCE_ROOT}/imap2020/include
                     $ENV{SOURCE_ROOT}/cci-stream-mta/include
                     $ENV{SOURCE_ROOT}/cci-faux-smtpd-async/include
                     $ENV{SOURCE_ROOT}/cci-daemon/include
                   )
#link location
link_directories( $ENV{DEV}/lib 
	              $ENV{DEV}/lib64
                  /usr/lib
                  $ENV{DEV}/chilkat-9.5.0-x86_64-linux-gcc/lib
                  $ENV{DEV}/chilkat-9.5.0-armv7a-hardfp-linux/lib
                  $ENV{DEV}/chilkat-9.5.0-armv7l-linux/lib
		          $ENV{DEV}/chilkat-9.5.0-aarch64-linux/lib)
                  

#library
add_library(cci_stream_event SHARED  cci_stream_event.cpp)
set_target_properties(cci_stream_event PROPERTIES
                                       VERSION 1.0.0
                                       SOVERSION 1) 

#binary
#add_executable(cci_mini_stream_event  cci_mini_stream_event.cpp)                               
                                   

#link libs
#target_link_libraries(cci_mini_stream_event  -lrdkafka++
#                                             -lrdkafka
#                                             -lrdkafka++
#                                             -lcurlpp
#                                             -lACE
#                                             -lACE_SSL
#                                             -lstdc++ 
#                                             -luuid
#                                             cci_stream_event
#                                             -lcci_mta_kernel
#                                             cci_daemon_kernel
#                                             -lpthread
#                                             -lchilkat-9.5.0 
#                                             cci_kafka_stream
#                                             cci_curlpp_stream)

#install
install_targets(/lib cci_stream_event)
#install_targets(/bin cci_mini_stream_event)

install (DIRECTORY ../../include/ 
         DESTINATION include)

