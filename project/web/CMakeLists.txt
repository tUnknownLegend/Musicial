cmake_minimum_required(VERSION 3.16)

project(Musicial CXX)

include_directories(
        ${BOOST_INCLUDE_DIRS}
        include
)


find_package(GTest REQUIRED)
find_package(Boost COMPONENTS system)
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.7.3 REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${nlohmann_json_INCDIR})


# Async Client
add_executable(client
        include/net_tools.h
        src/client.cpp
        include/response.h
        include/server_tools.h
        src/net_tools.cpp
        include/client_tools.h
        src/client.cpp
        include/shared_lib.h)
target_link_libraries(client ${Boost_LIBRARIES})


# Multithread Async Server
add_executable(server
        include/net_tools.h
        src/server.cpp
        src/connection.cpp
        include/request.h
        include/response.h
        include/router.h
        src/server_tools.cpp
        src/net_tools.cpp
        include/shared_lib.h)
target_link_libraries(server ${Boost_LIBRARIES} CURL::libcurl GTest::Main curl nlohmann_json::nlohmann_json)

set(SOURCES tests/run_tests.cpp tests/network_tests.cpp include/shared_lib.h)
add_executable(run_tests include/net_tools.h ${SOURCES})
target_link_libraries(run_tests GTest::GTest
        ${Boost_LIBRARIES}
        )