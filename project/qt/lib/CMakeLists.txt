cmake_minimum_required(VERSION 3.4)
project(QT_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" )

file(GLOB SOURCES *.cpp *.h)

set(SOURCES src/mainlib.cpp)

include_directories(${GTEST_INCDIR} include src tests)
add_subdirectory(src)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}  GTest::Main GTest::gmock)

include_directories(
        include
)

add_executable(client
        src/mainlib.cpp )
target_link_libraries(client)

