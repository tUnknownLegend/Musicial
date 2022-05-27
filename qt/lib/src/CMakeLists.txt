cmake_minimum_required(VERSION 3.0.0)
project(QT_SRC)

file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include/)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(../../../web/project/server/include)

message(${PROJECT_SOURCE_DIR}/../include)

add_library(${PROJECT_NAME} ${SOURCES} ../../../builtLibs/libserverLib.a)



set(Musicial_SRC_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(Musicial_SRC_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

target_link_libraries(QT_SRC ${CMAKE_SOURCE_DIR}/../../builtLibs/libserverLib.a )