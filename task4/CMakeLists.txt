cmake_minimum_required(VERSION 3.6)
project(task4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES format.cpp)

add_library(format ${SOURCE_FILES})
add_executable(task4 ${SOURCE_FILES})
target_link_libraries(task4 format)

set(SOURCES format.cpp)
install (TARGETS format DESTINATION lib)
install(FILES format.h DESTINATION include)