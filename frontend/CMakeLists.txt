cmake_minimum_required(VERSION 3.23)
project(frontend)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2/include)
set(SDL2_TTF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2_ttf/include)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

set(BACKEND_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../backend)
include_directories(${BACKEND_INCLUDE_DIR})

set(SDL2_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2/lib/x64)
set(SDL2_TTF_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2_ttf/lib/x64)
link_directories(${SDL2_LIBRARY_DIR} ${SDL2_TTF_LIBRARY_DIR})


add_library(frontend SHARED frontend.cpp)


target_link_libraries(frontend
        ${CMAKE_SOURCE_DIR}/../backend/libbackend.dll
        SDL2main SDL2 SDL2_ttf
        )
