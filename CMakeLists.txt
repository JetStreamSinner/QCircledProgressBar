cmake_minimum_required(VERSION 3.16)
project(CircledProgressBar)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOMOC ON)
set(Qt5Widgets_DIR "/home/alex/Qt/5.14.1/gcc_64/lib/cmake/Qt5Widgets")

find_package(Qt5Widgets CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(src main.cpp CircledProgressBar.cpp)

add_executable(CircledProgressBar ${src})
target_link_libraries(CircledProgressBar Qt5::Widgets)