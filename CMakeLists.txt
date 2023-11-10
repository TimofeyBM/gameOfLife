cmake_minimum_required(VERSION 3.23)
project(gameOfLifeBeta)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")
# Устанавливаем выходную директорию для .exe файла
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Указываем, что это GUI приложение (WIN32)
if (WIN32)
    set(GUI_TYPE WIN32)
endif (WIN32)

# Указываем директории для поиска заголовочных файлов
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/include)
set(SDL2_TTF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/include)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

set(FRONTEND_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/frontend)
include_directories(${FRONTEND_INCLUDE_DIR})

# Указываем директории для поиска библиотек
set(SDL2_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/lib/x64)
set(SDL2_TTF_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/lib/x64)
link_directories(${SDL2_LIBRARY_DIR} ${SDL2_TTF_LIBRARY_DIR})

set(FRONTEND_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/frontend)
link_directories(${FRONTEND_LIBRARY_DIR})

# Создаем исполняемый файл
add_executable(gameOfLifeBeta ${GUI_TYPE} main.cpp)

# Если вам нужны дополнительные опции компиляции, вы можете добавить их здесь.
# target_compile_options(gameOfLife PRIVATE ...)

# Указываем библиотеки для связывания
target_link_libraries(gameOfLifeBeta
        ${CMAKE_SOURCE_DIR}/frontend/libfrontend.dll
        ${CMAKE_SOURCE_DIR}/frontend/cmake-build-debug-mingw/libfrontend.dll.a
        SDL2main
        SDL2
        SDL2_ttf
        )

# Устанавливаем, что это WIN32_EXECUTABLE (GUI приложение)
#set_target_properties(gameOfLifeBeta PROPERTIES WIN32_EXECUTABLE TRUE)