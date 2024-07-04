# Game Boilerplate Generator

Simple application that generates a [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) project.

This application generates a project in C++ that is ready to use SDL3. Among these files is a very simplistic game engine (named __Basic Engine__ or __be__ for short) that handles the initilization, input, time, scenes and the shutdown.

The generated project is a [CMake](https://cmake.org/cmake/help/latest/) project. This project will fetch SDL3, which means that no SDL3 is required to be pre-installed.

⚠️ Fetching __SDL3__ takes some time. Please be patient 🙂

After the project generation it is ready to build, compile and run.

### Why not to create a library?

Generating all the source files gives more flexibily to adapt the engine as opposed to consume a library. This way it is possible to modify the engine.

## Requirements
Make sure you have the following tools installed:
- C++ Compiler
- CMake
- Git

## Build

```bash
cmake -B build
cmake --build build/
# This is optional to make the application callable from anywhere, but this requires a Release build in Windows!
sudo cmake --install build/
```

## Usage

```bash
path/to/build/gbgen -n MyGame
# You can also generate a project that is ready to use Vulkan
path/to/build/gbgen -n MyGame --with-vulkan

# Use --help for more information
```
