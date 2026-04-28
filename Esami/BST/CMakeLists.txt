cmake_minimum_required(VERSION 4.2)
project(BST C)

set(CMAKE_C_STANDARD 99)

add_executable(BST
        bst.c
        bst.h
        item.c
        item.h
        main.c)
