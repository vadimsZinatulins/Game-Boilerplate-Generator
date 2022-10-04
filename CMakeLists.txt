cmake_minimum_required(VERSION 3.10)

# Game Boilerplate Generator
project(gbgen VERSION 3.6)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

find_package(Threads REQUIRED)

add_subdirectory(src)
