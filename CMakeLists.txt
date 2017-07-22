cmake_minimum_required(VERSION 3.7)
project(tripbank)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Bank.cpp Bank.h Client.cpp Client.h Colorizer.cpp Colorizer.h)
add_executable(tripbank ${SOURCE_FILES})