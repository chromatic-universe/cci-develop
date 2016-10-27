#cmake cci_mini_kafka_run  william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.8)
#project
project(minikafkacpprun)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -Qunused-arguments  -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic -Qunused-arguments  -DNDEBUG -std=c++14")

#includes
include_directories( ${minikafkacpprun_SOURCE_DIR}
                     $ENV{DEV}/include
                     ../include
                   )
#link location
link_directories( /cci/dev_t/lib)

#binary
add_executable(cci_mini_kafka_run  cci_mini_kafka_run.cpp
                                   cci_kafka_stream.cpp
                                   cci_kafka_consumer.cpp 
                                   cci_kafka_producer.cpp
                                   cci_kafka_preamble.cpp
                                   cci_kafka_utils.cpp)
                               
                                   
                                   

#link libs
target_link_libraries(cci_mini_kafka_run -lrdkafka++ -lrdkafka -lprofiler )
