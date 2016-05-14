#cmake cci_mini_fuser  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.8)
#project
project(CCIMINIFUSER)

#cpp flags
set(CMAKE_C_FLAGS_DEBUG "-Wall -g -O0  -Qunused-arguments  -DDEBUG -std=c99 -D_FILE_OFFSET_BITS=64") 
set(CMAKE_C_FLAGS_RELEASE "-Wall -O3  -Qunused-arguments  -DNDEBUG -std=c99 -D_FILE_OFFSET_BITS=64")

#includes
include_directories( ${CCIMINIFUSER_SOURCE_DIR}
                     ${CMAKE_INSTALL_PREFIX}/include
                     /usr/include
                     ../../../include
                     /usr/include/glib-2.0 
					 /usr/lib/i386-linux-gnu/glib-2.0/include 
                    )

#link location
link_directories(  ${CMAKE_INSTALL_PREFIX}/lib
                   /usr/lib) 


#binary
add_executable(cci_mini_fuser cci_mini_fuser.c
                              mini_fuser_run.c)

#link libs
target_link_libraries(cci_mini_fuser -lglib-2.0
                                     -lgobject-2.0
                                     -lfuse)

#install
install_targets(/bin cci_mini_fuser)

                          





