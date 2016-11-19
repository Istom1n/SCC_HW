cmake_minimum_required(VERSION 3.6)
project(SCC_HW)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SCCSolver.h SCCSolver.cpp)
add_executable(SCC_HW ${SOURCE_FILES})