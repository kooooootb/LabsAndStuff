cmake_minimum_required(VERSION 3.20)
project(lab5)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ..)

add_executable(lab5 main.cpp Graph.cpp Graph.h)
