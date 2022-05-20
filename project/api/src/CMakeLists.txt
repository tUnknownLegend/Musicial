cmake_minimum_required(VERSION 3.0.0)
project(Musicial_SRC)

file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include/)

include_directories(${PROJECT_SOURCE_DIR}/include)

message(${PROJECT_SOURCE_DIR}/../include)

add_library(${PROJECT_NAME} ${SOURCES})

set(Musicial_SRC_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(Musicial_SRC_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)