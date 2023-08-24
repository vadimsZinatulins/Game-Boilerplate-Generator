cmake_minimum_required(VERSION 3.20)

# Game Boilerplate Generator
project(gbgen VERSION 3.6.1)

configure_file(config/config.h.in include/config.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(FetchContent)

FetchContent_Declare(
  SimpleTaskManager
  GIT_REPOSITORY https://github.com/vadimsZinatulins/SimpleTaskManager.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(SimpleTaskManager)

add_subdirectory(src)
