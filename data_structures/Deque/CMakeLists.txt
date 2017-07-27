cmake_minimum_required(VERSION 3.2)
project(Vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

set(SOURCE_FILES main.cpp)
add_executable(Vector ${SOURCE_FILES} deque.h deque.cpp iterator.cpp const_iterator.cpp )