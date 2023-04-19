cmake_minimum_required(VERSION 3.18)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab3_S_1 main_S_1.cpp)
add_executable(lab3_S_2 main_S_2.cpp)
add_executable(lab3_D main_D.cpp)

include_directories(lib_S_1)
include_directories(lib_S_2)
include_directories(lib_D)

add_subdirectory(lib_S_1)
add_subdirectory(lib_S_2)
add_subdirectory(lib_D)
add_subdirectory(tests)

target_link_libraries(lab3_S_1 lib_S_1)
target_link_libraries(lab3_S_2 lib_S_2)
target_link_libraries(lab3_D lib_D)