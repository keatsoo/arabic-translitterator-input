cmake_minimum_required(VERSION 3.0)

project(arabic-translitterator-input)

set(INCL_PATH src/includes/) 
set(SRCS src/main.cpp src/ArabicModelCore/ArabicModel.cpp src/ArabicModelCore/ArabicModel.hpp)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

add_executable(arabic-translitterator-input ${SRCS})
