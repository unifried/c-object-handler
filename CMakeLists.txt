cmake_minimum_required(VERSION 3.27)
project(off_reader C)

set(CMAKE_C_STANDARD 11)

add_executable(off_reader
        main.c
        object_file_handler.c
        files.c
)
