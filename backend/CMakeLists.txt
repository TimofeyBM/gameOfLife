cmake_minimum_required(VERSION 3.23)
project(backend)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_library(backend SHARED backend.cpp backend.h)

target_include_directories(backend PRIVATE ${CMAKE_SOURCE_DIR})
