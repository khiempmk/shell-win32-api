cmake_minimum_required(VERSION 3.13)
project(khiemShell)

set(CMAKE_CXX_STANDARD 14)

add_executable(khiemShell main.cpp Menu.h runProcess.h cdComand.h dirComand.h)
target_link_libraries(khiemShell libpsapi.a)