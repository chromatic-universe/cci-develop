#cmake cci-curator  william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.8)


message(STATUS ${CMAKE_CXX_COMPILER})
message(STATUS ${CMAKE_C_COMPILER})
#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Wall -g -O0  -Qunused-arguments  -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -Wall -O3  -Qunused-arguments  -DNDEBUG -std=c++14")

#includes
include_directories($ENV{DEV}/include
                    ./)
link_directories(${ccicurator_SOURCE_DIR}
                  ${CMAKE_INSTALL_PREFIX}/lib
                ) 

#shared library
add_executable(cci-curator     CuratorService.cpp
                               curator_types.cpp
                               curator_constants.cpp 
                               SharedService.cpp
                               shared_types.cpp
                               shared_constants.cpp
                               cci-curator.cpp
                               cci_curator_rpc.cpp
                               EventService.cpp)
                               
#link libs
target_link_libraries(cci-curator -levent -lthrift -lthriftnb)

#install
install_targets( /bin cci-curator)




