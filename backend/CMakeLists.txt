cmake_minimum_required(VERSION 3.23)
project(backend)
set(CMAKE_EXE_LINKER_FLAGS "-static")
# Установите стандарт C++ на 23.
set(CMAKE_CXX_STANDARD 23)

# Установите флаг -static для линковки с библиотеками статически.
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Уберите флаг -m64 для компиляции в 32-битном режиме.
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

# Установите каталог для вывода исполняемых файлов.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Создайте библиотеку backend и добавьте исходные файлы.
add_library(backend SHARED backend.cpp backend.h)

# Удалите флаги компилятора для 64-битного режима.
# set_target_properties(backend PROPERTIES COMPILE_FLAGS "-m64")

# Включите каталог исходных файлов проекта.
target_include_directories(backend PRIVATE ${CMAKE_SOURCE_DIR})
