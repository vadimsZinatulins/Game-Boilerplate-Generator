# Require CMake 3.29 or newer
cmake_minimum_required(VERSION 3.29)

# Define the project name (gbgen) and version (0.8)
project(gbgen VERSION 0.8)

# Generate a config.h file from config.h.in template
configure_file(config/config.h.in include/config.h)

# Set C++ requirements
set(CMAKE_CXX_STANDARD 20)                  # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED True)       # Make C++20 mandatory
set(CMAKE_EXPORT_COMPILE_COMMANDS True)     # Generate compilation database for tools
set(BUILD_SHARED_LIBS False)                # Build static libraries

# Enable FetchContent for downloading dependencies
include(FetchContent)

# Download and set up SimpleTaskManager library
message(STATUS "Fetching SimpleTaskManager")
FetchContent_Declare(
  SimpleTaskManager
  GIT_REPOSITORY https://github.com/vadimsZinatulins/SimpleTaskManager.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(SimpleTaskManager)

# Include the src directory which has its own CMakeLists.txt
add_subdirectory(src)
