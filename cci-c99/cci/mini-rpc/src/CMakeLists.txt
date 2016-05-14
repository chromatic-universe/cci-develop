#cmake cci_mini_rpc_run  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.8)
#project
project(CCIMINIRPCRUN)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0  -Qunused-arguments  -DDEBUG -std=C99")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -Qunused-arguments  -DNDEBUG -std=C99")

#includes
include_directories( ${CCIMINIRPCRUN_SOURCE_DIR}
                     ${CMAKE_INSTALL_PREFIX}/include
                     /usr/include
                     ../include
                     /usr/include/glib-2.0 
					 /usr/lib/i386-linux-gnu/glib-2.0/include 
                   )
#link location
link_directories( /dev_tools/lib /usr/lib /usr/local/lib) 

#binary
add_executable(cci_mini_rpc_run  cci_mini_clang_rpc.c 
                                 cci_mini_rpc_run.c 
                                 cci_mini_rpc_types.c )

#link libs
target_link_libraries(cci_mini_rpc_run -lglib-2.0
                                       -lgobject-2.0
                                       -lthrift_c_glib
                                       -lcci_thrift_glibc
                                       -lthrift
                                       -lthriftnb )

#install
install_targets(/bin cci_mini_rpc_run)


