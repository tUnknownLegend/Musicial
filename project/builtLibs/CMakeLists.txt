project(asd)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14 -Wall")

add_executable(asd asd.cpp libMusicial_API_LIB.a)

target_link_libraries(asd )
