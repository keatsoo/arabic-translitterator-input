cmake_minimum_required(VERSION 3.0)

project(arabic-translitterator-input)

set(SRC src/main.cpp)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")

add_executable(arabic-translitterator-input ${SRC})
