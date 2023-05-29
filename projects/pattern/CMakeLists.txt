# Message(sample message)

cmake_minimum_required(VERSION 3.6)

project(pattern)

add_library(process STATIC lib/Process.c)
add_library(interface STATIC lib/Interface.c)

include_directories(${CMAKE_SOURCE_DIR}/lib)

# link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(pattern src/main.c)

target_link_libraries(pattern process m interface) # m は math.h なぜかはわからん

# math.hを使う場合
# target_link_libraries(pattern PRIVATE m)