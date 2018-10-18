# cmake arm_cci_bootstrap  william k. johnson 2016


# version
cmake_minimum_required(VERSION 2.8)
# project
project(arm_cci_bootstrap)


#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0 -DDEBUG -std=c99")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -rdynamic -O9 -DRELEASE -std=c99")

set(CMAKE_SYSTEM_NAME  Android)
set(CMAKE_SYSTEM_VERSION 44)


# includes
include_directories($ENV{CCI_CHAIN}/include  
                    $ENV{CCI_ARM}/include/python2.7 )

# link
link_directories($ENV{CCI_ARM}/lib
                 $ENV{CCI_LIB})
                
#binary
add_executable(cci-bootstrap cci_bootstrap.c cci_daemon.c)

#link libs
target_link_libraries(cci-bootstrap -lpython2.7 -lcrystax -llog)
#install
install_targets(/bin_arm cci-bootstrap)

