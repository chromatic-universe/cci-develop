#cmake libcci_thrift_glibc  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.6)
#project
project(CCITHRIFTGLIBC)

#c flags
set(CMAKE_C_FLAGS_DEBUG "-fPIC -Wall -g -O0  -Qunused-arguments  -DDEBUG -std=c99")
set(CMAKE_C_FLAGS_RELEASE "-fPIC -Wall -O3  -Qunused-arguments  -DNDEBUG -std=c99")

#includes
include_directories(${CCITHRIFTGLIBC_SOURCE_DIR}
                    /usr/include/glib-2.0 
					/usr/lib/i386-linux-gnu/glib-2.0/include 
                    /dev_tools/include
                    /usr/include
                    ../include
                   )

link_directories(${CCITHRIFTGLIBC}) 

#shared library
add_library(cci_thrift_glibc SHARED shared_service.c shared_types.c)
#libs
target_link_libraries(cci_thrift_glibc -levent -lthrift_c_glib -lthrift -lthriftnb -lglib-2.0)

#install
install_targets( /lib cci_thrift_glibc)

