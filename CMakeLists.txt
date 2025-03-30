cmake_minimum_required(VERSION 3.23)
project(Rectangle)

set(CMAKE_CXX_STANDARD 20)

add_executable(Rectangle main.cpp Point.hpp Rectangle.hpp interface.hpp)
