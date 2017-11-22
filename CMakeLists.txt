cmake_minimum_required(VERSION 3.8)
project(LibraryKeeping)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c books.h books.c)
add_executable(LibraryKeeping ${SOURCE_FILES} books.h books.c)