
# version
cmake_minimum_required(VERSION 2.8)
# project
project(cci_trinity_tunnel)


#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g  -O0 -Qunused-arguments -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -Qunused-arguments -DRELEASE -std=c++14")



# includes
include_directories( ${cci_trinity_tunnel_SOURCE_DIR}
                    /usr/include
                    ./include
                   ) 

# link
link_directories(${cci_trinity_tunnel_SOURCE_DIR}
                 /usr/lib
                 /usr/lib/i386-linux-gnu/lib
                )
 
 #binary
add_executable(cci-trinity-tunnel  cci_trinity_tunnel.cpp 
                                   cci_trinity_acceptor.cpp
                                   cci_trinity_bridge.cpp 
                                   cci_trinity_options.cpp)
                                  
#link libs
target_link_libraries(cci-trinity-tunnel -lstdc++ -lpthread -lboost_thread -lboost_system -lboost_program_options
    ${cci_trinity_tunnel_SOURCE_DIR}/lib/libsqlite3.a) 


#install
install_targets(/bin  cci-trinity-tunnel)
install(DIRECTORY py/ 
         DESTINATION py)
install(FILES instance_id DESTINATION bin)
install(FILES lib/libsqlite3.a DESTINATION lib/libsqlite3.a)



