#cmake cpp_expansion william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.82)
#project
project(CPPEXPANSION)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Wall -g -O0  -Qunused-arguments  -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -Wall -O3  -Qunused-arguments  -DNDEBUG -std=c++14")

#includes
include_directories(../include
    $ENV{DEV}/include)

#executable
add_executable(cci_exp_test_run  test_cci_numeric_utils.cpp)

#link libs
target_link_libraries(cci_exp_test_run -lcci_expansion -lpthread -lgtest -lgtest_main)


