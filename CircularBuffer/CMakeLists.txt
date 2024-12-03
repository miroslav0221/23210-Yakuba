project(CircularBuffer)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(third_party/googletest)

include_directories(include)

add_executable(CircularBuffer src/main.cpp
        include/CircularBuffer.h
        src/CircularBuffer.cpp
        tests/tests_circular_buffer.cpp
)
add_executable(tests tests/tests_circular_buffer.cpp src/CircularBuffer.cpp)
target_link_libraries(CircularBuffer gtest gtest_main)

