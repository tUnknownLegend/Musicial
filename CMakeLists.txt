cmake_minimum_required(VERSION 3.16)
project(Musicial CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_CLANG_TIDY clang-tidy; -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)
set(INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/project/include")


add_library(Network STATIC project/src/Network.cpp)
target_include_directories(Network PUBLIC project/include)
add_executable(Musicial project/src/main.cpp)
target_link_libraries(Musicial Network)

find_package(GTest REQUIRED)
set(SOURCES tests/run_tests.cpp tests/network_tests.cpp project/src/Network.cpp)
add_executable(run_tests ${SOURCES})
target_link_libraries(run_tests GTest::GTest Network)



