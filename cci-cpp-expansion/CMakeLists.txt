#cmake cpp_expansion william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.82)
#project
project(CPPEXPANSION)

#tests
add_subdirectory(test)

#compiler
message(STATUS ${CMAKE_CXX_COMPILER})
message(STATUS ${CMAKE_C_COMPILER})
#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Wall -g -O0  -Qunused-arguments  -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -Wall -O3  -Qunused-arguments  -DNDEBUG -std=c++14")

#includes
include_directories(./include)
link_directories(${CPPEXPANSION_SOURCE_DIR})

#shared library
add_library(cci_expansion SHARED cci_complexity.cpp)
#executable
add_executable(cci_exp_run  cci_exp_run.cpp)

#link libs
target_link_libraries(cci_exp_run -lcci_expansion -lpthread)

#install
install_targets( /lib cci_expansion)

install_targets( /bin cci_exp_run)


