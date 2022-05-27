cmake_minimum_required(VERSION 3.16)

project(Musicial CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -Wall -ggdb3 -pthread -lcurl")
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_C_CLANG_TIDY clang-tidy; -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)
set(INCLUDE_DIRS "${CMAKE_SOURCE_DIR}")

find_package(GTest REQUIRED)
find_package(Boost COMPONENTS system)

add_subdirectory(web)
add_subdirectory(qt/lib)
add_subdirectory(api)
add_subdirectory(db)

#add_executable(run_tests project/server/include/net_tools.h ${SOURCES} )
target_link_libraries(run_tests
        Musicial_API_LIB GTest::GTest // fix
        ${Boost_LIBRARIES}
        )