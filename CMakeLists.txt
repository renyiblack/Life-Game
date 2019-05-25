cmake_minimum_required(VERSION 3.14)
project(life)

set(CMAKE_CXX_STANDARD 11)

include_directories( include )

add_executable(life src/main.cpp)