cmake_minimum_required(VERSION 3.0)

project(alifkey)

set(INCL_PATH src/includes/) 
set(SRCS src/main.cpp src/AlifKeyCore/ArabicModel.cpp src/AlifKeyCore/ArabicModel.hpp)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

add_executable(alifkey ${SRCS})
