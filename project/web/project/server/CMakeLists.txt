include_directories(
        ${BOOST_INCLUDE_DIRS}
        include
)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} -lcurl")

find_package(CURL REQUIRED)
find_package(Boost)
find_package(nlohmann_json 3.7.3 REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${nlohmann_json_INCDIR})

# Async Client
add_executable(client src/client.cpp include/response.h include/server_tools.h include/net_tools.h src/net_tools.cpp include/client_tools.h src/client.cpp)
target_link_libraries(client  ${Boost_LIBRARIES})


# Multithread Async Server
add_executable(server
        src/server.cpp
        src/connection.cpp
        include/request.h
        include/response.h
        include/router.h
        src/server_tools.cpp
        include/net_tools.h
        src/net_tools.cpp
        include/client.h)
target_link_libraries(server ${Boost_LIBRARIES} CURL::libcurl GTest::Main curl nlohmann_json::nlohmann_json)

