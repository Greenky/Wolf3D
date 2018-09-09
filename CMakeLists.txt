cmake_minimum_required(VERSION 3.9)
project(Wolf3D)

set(CMAKE_CXX_STANDARD 11)

find_library(SDL SDL2)
include_directories(frameworks/SDL2.framework/Headers)

add_executable(Wolf3D flat_test.c)

target_link_libraries(Wolf3D ${SDL})