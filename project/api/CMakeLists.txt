cmake_minimum_required(VERSION 3.10)
project(Musicial_API)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} -I -lcurl -Wall")

file(GLOB SOURCES *.cpp *.h)

find_package(GTest REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.7.3 REQUIRED)

include_directories(${GTEST_INCDIR} include src tests)
add_subdirectory(src)
include_directories(${curl_INCDIR})
include_directories(${nlohmann_json_INCDIR})

set(SOURCES src/api.cpp src/mainnn.cpp)


add_library(Musicial_API_LIB STATIC ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(Musicial_API_LIB ${Musicial_SRC_LIBRARIES} GTest::Main nlohmann_json::nlohmann_json curl libcurl curlcpp CURL::libcurl)


target_include_directories(${PROJECT_NAME} PUBLIC ${Musicial_API_INCLUDE_DIRS} ${Musicial_SRC_INCLUDE_DIRS})