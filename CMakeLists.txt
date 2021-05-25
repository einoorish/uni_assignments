cmake_minimum_required(VERSION 3.17)
project(uni_assignments)

set(CMAKE_CXX_STANDARD 14)

include_directories("4th term/OOP/Lab2")

add_executable(uni_assignments
        "4th term/OOP/Lab2/.gitignore"
        "4th term/OOP/Lab2/factory.cpp"
        "4th term/OOP/Lab2/factory.h"
        "4th term/OOP/Lab2/Lab2.pro"
        "4th term/OOP/Lab2/main.cpp"
        "4th term/OOP/Lab2/mainwindow.cpp"
        "4th term/OOP/Lab2/mainwindow.h"
        "4th term/OOP/Lab2/mainwindow.ui"
        "4th term/OOP/Lab2/solve.cpp"
        "4th term/OOP/Lab2/solve.h"
        "4th term/OOP/Lab2/strategy.cpp"
        "4th term/OOP/Lab2/strategy.h")
