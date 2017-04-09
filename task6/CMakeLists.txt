cmake_minimum_required(VERSION 3.6)
project(task6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES lazy_string.cpp lazy_string.h)
add_library(lazy_string ${SOURCE_FILES})

install (TARGETS lazy_string DESTINATION lib)

install(FILES ${SOURCE_FILES} DESTINATION include)