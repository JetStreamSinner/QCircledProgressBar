cmake_minimum_required(VERSION 3.16)
project(CircledProgressBar)

set(Qt5Widgets_DIR "/home/alex/Qt/5.14.1/gcc_64/lib/cmake/Qt5Widgets")


find_package(Qt5Widgets CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(CircledProgressBar main.cpp)