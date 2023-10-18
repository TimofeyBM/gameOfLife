cmake_minimum_required(VERSION 3.23)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/include)
set(SDL2_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/lib/x64)

set(SDL2_TTF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/include)
set(SDL2_TTF_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/lib/x64)

if (WIN32)
    set(GUI_TYPE WIN32)
endif (WIN32)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIR} ${SDL2_TTF_LIBRARY_DIR})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(gameOfLife  ${GUI_TYPE} main.cpp backend/backend.cpp frontend/frontend.cpp)

target_link_libraries(gameOfLife SDL2main SDL2 SDL2_ttf)

add_subdirectory(backend)
add_subdirectory(frontend)
