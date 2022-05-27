cmake_minimum_required(VERSION 3.4)
project(QT_LIB)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14 -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp *.h)

set(SOURCES src/mainlib.cpp)
set(HEADERS include/mainlib.h)

include_directories(${GTEST_INCDIR} include src tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}  GTest::Main GTest::gmock ${CMAKE_SOURCE_DIR}/../../builtLibs/libserverLib.a)


#add_executable(run_tests_QT test/test.cpp ${SOURCES} ${HEADERS})
#target_link_libraries(run_tests_QT GTest::GTest)
