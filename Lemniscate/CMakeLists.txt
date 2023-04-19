cmake_minimum_required(VERSION 3.20)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2 main.cpp)

include_directories(lemniscate)

add_subdirectory(lemniscate)
add_subdirectory(lemniscate-tests)

target_link_libraries(lab2 lemniscate)