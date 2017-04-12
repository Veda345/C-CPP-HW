cmake_minimum_required(VERSION 3.6)
project(task4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES )
add_library(format ${SOURCE_FILES})

install (TARGETS format DESTINATION lib)

install(FILES ${SOURCE_FILES} DESTINATION include)