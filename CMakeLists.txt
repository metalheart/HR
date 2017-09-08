cmake_minimum_required(VERSION 3.8)
project(swap)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES swap-nodes-algo/main.cpp)
add_executable(swap ${SOURCE_FILES})