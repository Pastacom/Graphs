cmake_minimum_required(VERSION 3.21)
project(Graphs)

set(CMAKE_CXX_STANDARD 20)

add_executable(Graphs main.cpp Menu.cpp Menu.h Reader.cpp Reader.h Graph.h Graph.cpp)
