cmake_minimum_required(VERSION 3.20)

project(qtApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(qtApp src/main.cpp)

target_link_libraries(qtApp PRIVATE Qt5::Widgets)