cmake_minimum_required(VERSION 3.20)

# Game Boilerplate Generator
project(gbgen VERSION 3.6.1)

configure_file(config/config.h.in include/config.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

find_package(Threads)
find_package(SimpleTaskManager)

add_subdirectory(src)
