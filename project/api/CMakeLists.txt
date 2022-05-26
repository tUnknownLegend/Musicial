cmake_minimum_required(VERSION 3.10)
project(Musicial_API)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14 -Wall -lcurl")
set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS}")

file(GLOB SOURCES *.cpp *.h)

find_package(GTest REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.7.3 REQUIRED)

include_directories(${GTEST_INCDIR} include src tests)
#add_subdirectory(src)
include_directories(${CURL_INCLUDE_DIR})
include_directories(${nlohmann_json_INCDIR})

set(SOURCES src/api.cpp src/apiSpotify.cpp)
set(HEADERS include/api.h include/apiSpotify.h include/apiYoutube.h)


add_library(Musicial_API_LIB STATIC ${SOURCES} ${HEADERS})
#add_executable(${PROJECT_NAME} ${SOURCES})


#target_include_directories(${PROJECT_NAME} PUBLIC)


target_link_libraries(Musicial_API_LIB  PUBLIC ${Musicial_SRC_LIBRARIES} ${CURL_LIBRARIES} CURL::libcurl GTest::Main curl nlohmann_json::nlohmann_json)
