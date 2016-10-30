#cmake arm_kafka_ext william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.82)
#project
project(arm_kafka_ext)
#uses crystax 10.3 ndk & custom toolchain

#cpp flags
set(CMAKE_C_FLAGS_DEBUG "-fPIC -Wall -g -O0  -DDEBUG -std=c99")
set(CMAKE_C_FLAGS_RELEASE "-fPIC -Wall -O3   -DNDEBUG -std=c99")

#include
include_directories( ../include
                     $ENV{DEV}/include
                     /usr/include/python2.7
                    )
#link
link_directories( $ENV{DEV}/lib
                  /usr/lib)

#shared library
add_library(_cci_rdkafka_py SHARED cci_mini_kafka.c
                                   cci_rdkafka_py_wrap.c)
#target prefix for pythone disutils and setuptools                               
set_target_properties(_cci_rdkafka_py PROPERTIES PREFIX "")

#binaries
#python extension module test
add_executable(cci_ext_k  test.c cci_kafka_async_q.c)
#sink q
add_executable(cci_kafka_sink  cci_kafka_sink.c
                               cci_kafka_async_q.c
                               cci_daemon.c
                               cci_mini_kafka.c)
add_executable(cci_kafka_source  cci_kafka_q_dispatch.c
                                 cci_kafka_async_q.c
                                 cci_daemon.c
                                 cci_mini_kafka.c)
                        
#source dispatch

#link libs
target_link_libraries(_cci_rdkafka_py -lrdkafka -lnanomsg)
target_link_libraries(cci_ext_k -lrdkafka -lnanomsg)
target_link_libraries(cci_kafka_sink -lrdkafka -lnanomsg)
target_link_libraries(cci_kafka_source -lrdkafka -lnanomsg)

#install
install_targets(/bin  cci_ext_k)
install_targets(/bin  cci_kafka_sink)
install_targets(/bin  cci_kafka_source)
install_targets(/lib  _cci_rdkafka_py)

