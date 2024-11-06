#cmake_minimum_required(VERSION 3.29)
#project(CircularBuffer)
#
#set(CMAKE_CXX_STANDARD 17)
##set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
#
#
#add_subdirectory(googletest)
##enable_testing()
#
#include_directories(include)
#
#add_executable(CircularBuffer src/main.cpp
#        include/CircularBuffer.h
#        src/CircularBuffer.cpp
#        tests/tests_circular_buffer.cpp
#)
##add_executable(tests tests/tests_circular_buffer.cpp src/CircularBuffer.cpp)
##add_executable(test_lab1 main.cpp CircularBuffer.cpp)
#target_link_libraries(CircularBuffer gtest gtest_main)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")

cmake_minimum_required(VERSION 3.22)
project(CircularBuffer)

set(CMAKE_CXX_STANDARD 17)

add_executable(CircularBuffer src/main.cpp
        src/CircularBuffer.cpp
)

target_include_directories(CircularBuffer PUBLIC include)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests/tests_circular_buffer.cpp src/CircularBuffer.cpp)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests GTest::gtest_main)