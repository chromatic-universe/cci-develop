#cmake arm_kafka_ext william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.82)
#project
project(arm_kafka_ext)

#cpp flags
set(CMAKE_C_FLAGS_DEBUG "-fPIC -Wall -g -O0  -DDEBUG -std=c99")
set(CMAKE_C_FLAGS_RELEASE "-fPIC -Wall -O3   -DNDEBUG -std=c99")

include_directories( ../include
                     $ENV{DEV}/include
                     /usr/include/python2.7
                    )

link_directories( $ENV{DEV}/lib
                  /usr/lib)

#shared library
add_library(_cci_rdkafka_py SHARED cci_mini_kafka.c
                                   cci_rdkafka_py_wrap.c
                                   test.c)
set_target_properties(_cci_rdkafka_py PROPERTIES PREFIX "")

add_executable(cci_ext_k  test.c)
              
#link libs
target_link_libraries(_cci_rdkafka_py -lrdkafka)
target_link_libraries(cci_ext_k -lrdkafka)


install_targets(/bin  cci_ext_k)
install_targets(/lib  _cci_rdkafka_py)

