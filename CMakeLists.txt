cmake_minimum_required(VERSION 2.6)
project(sketch)

add_definitions(-Wall -Wextra -Werror -Wno-unused-parameter -std=c99)
add_definitions(-O0 -g)
include_directories(Include)

add_subdirectory(Source build/sketch)
add_subdirectory(Test build/test)
