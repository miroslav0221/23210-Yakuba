cmake_minimum_required(VERSION 3.29)
project(lab2_GameofLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2_GameofLife src/main.cpp
        src/Model.cpp
        src/View.cpp
        src/Controller.cpp
        include/Controller.h
)

target_include_directories(lab2_GameofLife PUBLIC include)