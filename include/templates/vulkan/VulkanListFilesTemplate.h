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

# Do not install SDL2
set(SDL2_DISABLE_INSTALL CACHE BOOL On FORCE)
# Build only SDL2 Static Lib
set(SDL_SHARED_ENABLED_BY_DEFAULT CACHE BOOL Off FORCE)
message(STATUS "Fetching and configuring SDL2")
FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-2.28.2  # Change this freely
)

FetchContent_MakeAvailable(SDL2)

# Find Vulkan package
find_package(vulkan REQUIRED)

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
		SDL2::SDL2-static
		SDL2::SDL2main
        Vulkan::Vulkan
)
)" };
