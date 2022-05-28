cmake_minimum_required(VERSION 3.10)
project(apilib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror")
set(CMAKE_C_CPPCHECK "cppcheck")
set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=*")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp *.h)

find_package(GTest REQUIRED)
find_package(CURL REQUIRED)

include_directories(${GTEST_INCDIR})
include_directories(${curl_INCDIR})
include_directories(${nlohmann_json_INCDIR})

add_executable(${PROJECT_NAME} ${SOURCES} tests.cpp)

target_link_libraries(${PROJECT_NAME} GTest::Main curl)