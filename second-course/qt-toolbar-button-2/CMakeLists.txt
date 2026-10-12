cmake_minimum_required(VERSION 3.20)

project(qtApp LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(qtApp
    main.cpp
    toolbutton.h
    toolbutton.cpp
    resources.qrc
)

target_link_libraries(qtApp PRIVATE Qt5::Widgets)