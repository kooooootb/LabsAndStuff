include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests_S_1 test_S_1.cpp)

target_link_libraries(runTests_S_1 gtest gtest_main)
target_link_libraries(runTests_S_1 lib_S_1)

add_executable(runTests_S_2 test_S_2.cpp)

target_link_libraries(runTests_S_2 gtest gtest_main)
target_link_libraries(runTests_S_2 lib_S_2)

add_executable(runTests_D test_D.cpp)

target_link_libraries(runTests_D gtest gtest_main)
target_link_libraries(runTests_D lib_D)

include_directories(../..)