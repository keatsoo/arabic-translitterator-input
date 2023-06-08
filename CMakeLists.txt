cmake_minimum_required(VERSION 3.0)

project(arabic-translitterator-input)

set(SRCS src/main.cpp src/includes/fuzzySearch.hpp src/includes/fuzzySearch.cpp src/includes/levensteinDistance.hpp src/includes/levensteinDistance.cpp)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")

add_executable(arabic-translitterator-input ${SRCS})
