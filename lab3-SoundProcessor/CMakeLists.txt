cmake_minimum_required(VERSION 3.29)
project(lab3_SoundProcessor)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3_SoundProcessor src/main.cpp
        src/Factory.cpp
        src/MixConverter.cpp
        src/MuteConverter.cpp
        src/DataSource.cpp
        src/DataWriter.cpp
        src/Processor.cpp
        src/ChangeVolConverter.cpp)

target_include_directories(lab3_SoundProcessor PUBLIC include)