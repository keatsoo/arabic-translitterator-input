cmake_minimum_required(VERSION 3.0)

project(arabic-translitterator-input)

set(INCL_PATH src/includes/) 
set(SRCS src/main.cpp ${INCL_PATH}/fuzzySearch.hpp ${INCL_PATH}/fuzzySearch.cpp ${INCL_PATH}/levensteinDistance.hpp ${INCL_PATH}/levensteinDistance.cpp ${INCL_PATH}/transliterateNaively.cpp ${INCL_PATH}/transliterateNaively.hpp ${INCL_PATH}/jaroWinklerDistance.hpp ${INCL_PATH}/jaroWinklerDistance.cpp)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")

add_executable(arabic-translitterator-input ${SRCS})
