include_directories(
        ${BOOST_INCLUDE_DIRS}
        include
)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -pthread")

find_package(Boost)


# Async Client
#add_executable(client src/client.cpp include/response.h include/server_tools.h include/net_tools.h src/net_tools.cpp include/client_tools.h)
#target_link_libraries(client  ${Boost_LIBRARIES})


# Multithread Async Server
add_executable(server
        src/server.cpp
        src/connection.cpp
        include/request.h
        include/response.h
        include/router.h
        src/server_tools.cpp
        include/net_tools.h
        src/net_tools.cpp
        include/client.h)
target_link_libraries(server ${Boost_LIBRARIES})

