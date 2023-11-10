cmake_minimum_required(VERSION 3.23)
project(frontend)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")
# Убираем флаг установки 64-битной архитектуры
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

# Устанавливаем выходную директорию для .dll файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2/include)
set(SDL2_TTF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2_ttf/include)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

set(BACKEND_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../backend)
include_directories(${BACKEND_INCLUDE_DIR})

# Указываем директории для поиска библиотек
set(SDL2_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2/lib/x64)  # Используйте x86 для 32-битной архитектуры
set(SDL2_TTF_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../lib/SDL2_ttf/lib/x64)  # Используйте x86 для 32-битной архитектуры
link_directories(${SDL2_LIBRARY_DIR} ${SDL2_TTF_LIBRARY_DIR})


# Создаем .dll библиотеку
add_library(frontend SHARED frontend.cpp)


target_link_libraries(frontend
        ${CMAKE_SOURCE_DIR}/../backend/libbackend.dll
        ${CMAKE_SOURCE_DIR}/../backend/cmake-build-debug-mingw/libbackend.dll.a# Связь с библиотекой backend
        SDL2main SDL2 SDL2_ttf
        )
# Если вам нужны дополнительные опции компиляции, вы можете добавить их здесь.
# target_compile_options(gameOfLifeFrontend PRIVATE ...)

# Указываем библиотеки для связывания
