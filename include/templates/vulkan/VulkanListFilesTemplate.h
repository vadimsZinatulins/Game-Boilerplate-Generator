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
        be/vulkan/device_picker/BaseCriteria.cpp
        be/vulkan/device_picker/ExtensionCriteria.cpp
        be/vulkan/device_picker/QueueCriteria.cpp
        be/vulkan/device_picker/DevicePicker.cpp
        be/vulkan/Surface.cpp
        be/vulkan/PhysicalDevice.cpp
        be/vulkan/Device.cpp
        be/vulkan/Swapchain.cpp
        be/vulkan/ShaderModule.cpp
        be/vulkan/Pipeline.cpp
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

# Copile every shader file (.vert, .frag) to SPIR-V and output them to resources/shaders
file(GLOB_RECURSE SHADER_SOURCES "${CMAKE_SOURCE_DIR}/shaders/*.vert" "${CMAKE_SOURCE_DIR}/shaders/*.frag")
foreach(SHADER ${SHADER_SOURCES})
  get_filename_component(SHADER_NAME ${SHADER} NAME_WE)
  set(SHADER_SPIRV "${CMAKE_SOURCE_DIR}/resources/shaders/${SHADER_NAME}.spv")
  add_custom_command(
    OUTPUT ${SHADER_SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/resources/shaders/"
    COMMAND glslc ${SHADER} -o ${SHADER_SPIRV}
    DEPENDS ${SHADER}
    COMMENT "Compiling shader ${SHADER_NAME}"
  )
  list(APPEND SPIRV_BINARY_FILES ${SHADER_SPIRV})
endforeach()

add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})
add_dependencies(${PROJECT_NAME} Shaders)

# Copy resources to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
)" };
