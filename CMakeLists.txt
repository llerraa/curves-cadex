cmake_minimum_required(VERSION 3.10)
project(CadexCurves CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека кривых (пункт 7 тз)
# Собирается как SHARED (.so / .dll)
# Чтобы собрать как статическую библиотеку надо заменить SHARED на STATIC.

add_library(curves SHARED
    Curves.cpp
    Curves.h
)

target_include_directories(curves PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Исполняемый файл 

add_executable(cadex_curves main.cpp)
target_link_libraries(cadex_curves PRIVATE curves)

# Предупреждения компилятора 

if (MSVC)
    target_compile_options(curves       PRIVATE /W4)
    target_compile_options(cadex_curves PRIVATE /W4)
else()
    target_compile_options(curves       PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(cadex_curves PRIVATE -Wall -Wextra -Wpedantic)
endif()
