cmake_minimum_required(VERSION 3.7)
project(2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        "Heap Clion/L_Heap.c"
        "Heap Clion/L_Heap.h"
        "Heap Clion/L_Utility.c"
        "Heap Clion/L_Utility.h"
        "Heap Clion/main.c")

add_executable(2 ${SOURCE_FILES})