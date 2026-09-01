cmake_minimum_required(VERSION 4.2)
project(Sorting_algorithms C)

set(CMAKE_C_STANDARD 99)

add_executable(Sorting_algorithms insertionSort.c
        mergeSort.c)
