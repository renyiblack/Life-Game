cmake_minimum_required(VERSION 3.14)
project(glife)

set(CMAKE_CXX_STANDARD 11)

include_directories( include )

add_executable(glife src/main.cpp src/lodepng.cpp)