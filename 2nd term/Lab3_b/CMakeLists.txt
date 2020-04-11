cmake_minimum_required(VERSION 3.15)
project(Lab3_b)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3_b
        CountingSort.cpp
        CountingSort.h
        Item.cpp
        Item.h
        main.cpp
        QuickSort.cpp
        QuickSort.h
        RadixSort.cpp
        RadixSort.h)
