#pragma once

const auto VULKAN_ROOT_LISTFILE_TEMPLATE { R"(#Minimum cmake version required to run this text file
cmake_minimum_required(VERSION 3.20)

# Project name
project({NAME} VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
# Force the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Generate compile commands (this is for vim)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(FetchContent)

# Fetch SDL3
set(SDL_STATIC TRUE CACHE BOOL "Build a SDL static library")
FetchContent_Declare(
	SDL
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG main  # Replace this with a particular git tag or git hash
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
message(STATUS "Using SDL3 via FetchContent")
FetchContent_MakeAvailable(SDL)
set_property(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl-src" PROPERTY EXCLUDE_FROM_ALL TRUE)

# Find Vulkan package
find_package(Vulkan REQUIRED)

# Project configuration file
configure_file(config/config.h.in "${PROJECT_SOURCE_DIR}/include/config.h")

add_subdirectory(src)
)" };


const auto VULKAN_SRC_LISTFILE_TEMPLATE { R"(# Create the executable
add_executable(${PROJECT_NAME})

# Basic Engine source files
target_sources(${PROJECT_NAME}
	PRIVATE
		be/KeyManager.cpp
		be/MouseManager.cpp
		be/Time.cpp
		be/Cronometer.cpp
		be/Random.cpp
		be/SceneManager.cpp
)

# Basic Engine Vulkan source files
target_sources(${PROJECT_NAME}
	PRIVATE
        be/vulkan/Instance.cpp
        be/vulkan/DebugMessenger.cpp
)

# Game core source files
target_sources(${PROJECT_NAME}
	PRIVATE
		MainScene.cpp
		{NAME}.cpp
		main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Libraries to link to the project
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		SDL3::SDL3-static
        Vulkan::Vulkan
)
)" };
