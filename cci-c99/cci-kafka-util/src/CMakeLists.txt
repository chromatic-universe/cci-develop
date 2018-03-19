#cmake cci_mini_kafka_run  william k. johnson 2016

#version
cmake_minimum_required(VERSION 3.2)
#project
project(cci-kafka-util)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -Qunused-arguments  -DDEBUG -std=c99")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic -Qunused-arguments  -DNDEBUG -std=c99")

#includes
include_directories( ${cci-kafka_utilSOURCE_DIR}
                     /usr/include/glib-2.0
                     $ENV{DEV}/include
                     /usr/lib/i386-linux-gnu/glib-2.0/include
                     /usr/lib/x86_64-linux-gnu/glib-2.0/include
                     /usr/lib/arm-linux-gnueabihf/glib-2.0/include
                     ../include
	             ../../include                   
                   )
#link location
link_directories( $ENV{DEV}/lib)

#library
add_library(cci_kafka_utils SHARED   cci_mini_kafka.c)

target_link_libraries(cci_kafka_utils  -lrdkafka)
set_target_properties(cci_kafka_utils PROPERTIES
                                      VERSION 1.0.0
                                      SOVERSION 1) 



add_executable(chk-kafka mini_kafka_run.c)                               
                                   

#link libs
target_link_libraries(chk-kafka  -lrdkafka
                                 -lglib-2.0
                                  cci_kafka_utils)

#install
install_targets(/lib cci_kafka_utils)
install_targets(/bin chk-kafka)

install (DIRECTORY ../include/ 
         DESTINATION include)

