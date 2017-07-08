#cmake cci_mini_kafka_run  william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.8)
#project
project(cci-kafka-cpp-stream)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -Qunused-arguments  -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic -Qunused-arguments  -DNDEBUG -std=c++14")

#includes
include_directories( ${cci-kafka-cpp-streamSOURCE_DIR}
                     $ENV{DEV}/include
                     ../include
	             ../../include
                     
                   )
#link location
link_directories( $ENV{DEV}/lib)

#library
add_library(cci_kafka_stream SHARED  cci_kafka_stream.cpp
                                     cci_kafka_consumer.cpp 
                                     cci_kafka_producer.cpp
                                     cci_kafka_preamble.cpp
                                     cci_kafka_utils.cpp)
set_target_properties(cci_kafka_stream PROPERTIES
                                       VERSION 1.0.0
                                       SOVERSION 1) 


#binary
add_executable(cci_mini_kafka_run  cci_mini_kafka_run.cpp)                               
                                   

#link libs
target_link_libraries(cci_mini_kafka_run -lrdkafka++
		                         -lrdkafka
					 cci_kafka_stream)

#install
install_targets(/lib cci_kafka_stream)
install_targets(/bin cci_mini_kafka_run)

install (DIRECTORY ../include/ 
         DESTINATION include)

