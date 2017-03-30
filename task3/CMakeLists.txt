cmake_minimum_required(VERSION 3.6)
project(task3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES rational.h rational.cpp)
add_library(rational ${SOURCE_FILES})

install (TARGETS rational DESTINATION lib)

install(FILES ${SOURCE_FILES} DESTINATION include)