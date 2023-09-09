# Game Boilerplate Generator

Simple application that generates a [SDL2](https://www.libsdl.org/download-2.0.php) project.

This application generates C++ files already with code ready to use SDL2 (and optionally SDL2-image). Among these files is a very simplistic game engine (name __Basic Engine__ or __be__ for short) that handles the initilization, input, time, scenes and the shutdown.

The generated project is another [Cmake](https://cmake.org/cmake/help/latest/) project. This project will fetch SDL2 (and optionally SDL2-image), which means that no SDL2 is required to be installed.

⚠️ Fetching __SDL2__ takes some time, and fetching __SDL2-image__ takes even more time. Please be patient 🙂

After the project generation it is ready to build, compile and run.

### Why not to create a library?

Generating all the source files for the game engine more flexibility as opposed to having a library. This way it is possible to adapt the game engine whenever needed.

## Dependencies

### C++ Compiler

You need a C++ compiler (for example clang or gcc) to this project (as well as generated project).

### CMake

To build this project you need CMake. Also to build the generated project you also need CMake.

```bash
sudo apt-get install cmake
```

## Installation

```bash
cmake -B build
cmake --build build/
# This is optional to make the application callable from anywhere
sudo cmake --install build/
```

## Usage

```bash
path/to/app/gbgen MyGame
# Or if sudo cmake --install build/ has been run
gbgen --name MyGame
```

### Output

The output project structure is as follows:

```
MyGame/
|-config/
| '-config.h.in
|-include/
| |-be/
| | |-Cronometer.h
| | |-Game.h
| | |-KeyManager.h
| | |-MouseManager.h
| | |-Random.h
| | '-Time.h
| '-MyGame.h
|-src/
| |-be/
| | |-Cronometer.cpp
| | |-Game.cpp
| | |-KeyManager.cpp
| | |-MouseManager.cpp
| | |-Random.cpp
| | '-Time.cpp
| |-MyGame.cpp
| '-main.cpp
'-CMakeLists.txt
```

### In code usage

**Quick Start**

Your game logic should be inside *Scenes*. The generated code already provide *MainScene* and it is a good startup point.

```cpp
#include "MainScene.h"

#include <SDL2/SDL.h>

void MainScene::initialize()
{
    // This method only gets called once before update and render 
    // This is a good place to initialize stuff, such as textures
    // or other resources.
}

void MainScene::shutdown()
{
    // This method only gets calle once after update and render
    // This is a good place to do cleanup, such os closing files 
    // or freeing resources
}

void MainScene::update()
{
	// This gets called once every frame.
    // The game logic should go here.
}

void MainScene::render(SDL_Renderer *renderer)
{
	// This gets called once every frame.
    // All the rendering should be done here
}

```

The *Scenes* are managed as [stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)) and the top *Scene* is considered to be the current active *Scene*. *Scenes* are _initialized_ and _shutdown_ when they are pushed and pop to/from the stack respectively. They are managed by *SceneManager* class as such:

```cpp
// Pushes a scene to the stack and will be the current
// active scene next frame (the initialization of the Scene will be
// called at the end of the current frame).
be::SceneManager::getInstance().pushScene<PauseScene>();

// Pops the current active scene from the stack and the current active
// scene in the next frame will be the next scene in the stack (the 
// shutdown of the scene will be called at the end of the current frame).
be::SceneManager::getInstance().popScene();

// Pops the current scene from the stack and pushes the new scene (at
// the end of the frame the initialization of the new scene will be
// called and then the shutdown)
be::SceneManager::getInstance().swap<LevelTwoScene>();
```

For player input you can use *KeyManager* and *MouseManager* classes for input from keyboard and input from mouse respectively.
