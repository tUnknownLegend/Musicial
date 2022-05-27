cmake_minimum_required(VERSION 3.14)
project(run_tests_QT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${QT_LIB_INCLUDE_DIRS} ${QT_LIB_SRC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SOURCES} ${HEADERS} GTest::Main)
