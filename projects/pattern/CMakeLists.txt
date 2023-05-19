cmake_minimum_required(VERSION 3.0)

project(pattern)

add_library(process STATIC lib/Process.c)

include_directories(${CMAKE_SOURCE_DIR}/lib)

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(pattern src/main.c)

target_link_libraries(pattern process)