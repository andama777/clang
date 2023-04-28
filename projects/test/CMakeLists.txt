# Cmakelists.txt

cmake_minimum_required(VERSION 3.0)

project(game)

# file(GLOB_RECURSE SOURCES "src/*.c")

# set(CMAKE_C_FLAGS "-Wall -O1")

add_library(window STATIC lib/Window.c)

add_library(layer STATIC lib/Layer.c)

add_library(clock STATIC lib/Clock.c)

link_directories(${CMAKE_SOURCE_DIR}/lib)

# include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(game src/main.c)

target_link_libraries(game window layer clock)