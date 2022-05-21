cmake_minimum_required(VERSION 3.16)

project(Musicial CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -Wall -ggdb3 -pthread")
#set(CMAKE_C_CLANG_TIDY clang-tidy; -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)
set(INCLUDE_DIRS "${CMAKE_SOURCE_DIR}")

find_package(GTest REQUIRED)
find_package(Boost COMPONENTS system)

add_subdirectory(project/server)


set(SOURCES tests/run_tests.cpp tests/network_tests.cpp)
add_executable(run_tests project/server/include/net_tools.h ${SOURCES} )
target_link_libraries(run_tests GTest::GTest
        ${Boost_LIBRARIES}
        )

