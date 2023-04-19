project(lemniscateTests)

# fetch tests libs
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# windows thing
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# enable gtest
FetchContent_MakeAvailable(googletest)
# enable tests itself
enable_testing()
# configure executable
add_executable(lemniscateTests Test.cpp)
# link with gtest lib
target_link_libraries(lemniscate GTest::gtest_main)
# dunno
include(GoogleTest)
gtest_discover_tests(lemniscateTests)
# include lemniscate things
target_include_directories(lemniscateTests PUBLIC "${Project_root}/monitor")
target_link_libraries(lemniscateTests lemniscate)
