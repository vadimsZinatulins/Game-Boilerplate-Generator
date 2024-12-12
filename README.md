# Game Boilerplate Generator

Simple application that generates a [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) project with a basic game engine structure.

## Features
- Generates a complete C++ project using SDL3
- Includes a lightweight game engine (Basic Engine or __be__) that handles:
  - Initialization and shutdown
  - Input management
  - Time management 
  - Scene management
- Optional components:
  - SDL3_image support
  - Basic 3D math library
  - Configurable logging

The generated project uses [CMake](https://cmake.org/cmake/help/latest/) and automatically fetches SDL3 dependencies, so no pre-installed SDL3 is required.

⚠️ Note: Initial SDL3 fetching may take some time during first build.

### Why Generate Files Instead of Using a Library?

Generating source files provides more flexibility than consuming a library. This approach allows developers to easily modify and adapt the engine code to their specific needs.

## Requirements
Make sure you have the following tools installed:
- C++ Compiler
- CMake (3.29 or higher)
- Git

## Build and Install

```bash
# Configure
cmake -B build

# Build
cmake --build build/

# Install (several options):
# 1. System-wide installation (requires root/admin)
sudo cmake --install build/

# 2. Custom installation path
cmake --install build/ --prefix /custom/path

# 3. Install only runtime component
cmake --install build/ --component runtime
```

## Usage

```bash
# Basic project
gbgen -n MyGame

# Additional options:
gbgen -n MyGame --with-sdl-image  # Include SDL3_image support
gbgen -n MyGame --with-math       # Include basic 3D math library
gbgen -n MyGame --no-logs         # Disable logging

# Use --help for more information
```
