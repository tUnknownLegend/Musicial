cmake_minimum_required(VERSION 3.21)
project(musicial)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14 -Wall")

find_package(PostgreSQL REQUIRED)
#target_include_directories(musicial PRIVATE ${PostgreSQL_INCLUDE_DIRS})
#target_link_libraries(musicial PRIVATE ${PostgreSQL_LIBRARIES})

include_directories(.
#        ~/Downloads/libpqxx-6.4/include/
        /usr/local/opt/libpq/include
        /usr/local/Cellar/boost/1.78.0_1/include
        )

add_executable(musicial
        main.cpp
        db.cpp
        db.h)


