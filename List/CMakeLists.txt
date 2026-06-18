cmake_minimum_required(VERSION 4.2)
project(List C)

set(CMAKE_C_STANDARD 99)

add_executable(List main.c
        "list .c"
        list.h)
