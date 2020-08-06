cmake_minimum_required(VERSION 3.8)
project(4__Esercizio_4___Code_a_priorita)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        "L_Heap.c"
        "L_Heap.h"
        "L_Utility.c"
        "L_Utility.h"
        "main.c")

add_executable(4__Esercizio_4___Code_a_priorita ${SOURCE_FILES})