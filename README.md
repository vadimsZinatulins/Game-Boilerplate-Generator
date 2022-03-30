# Game Boilerplate Generator

Simple application used to create boilerplate for [SDL2](https://www.libsdl.org/download-2.0.php).
This project will generate all files needed to build and run an SDL2 project. This is not a library nor it generates one, this is an application that will create an file structure and some files to start using SDL2.

### Why not to create a library?

Every time I start a new project (or want to make a quick test) with SDL2 I need to write a lot of boilerplate code (create a file structure, create CMakeLists.txt file, create classes that manage key and mouse input, a core class that initializes SDL2 and few more things) that I do not want to write every time I create this project (It's just a huge waste of time) so I decided to create an application that generates all these files for me.

Also, by generating the boilerplate I've got more flexibility to make changes to the core than I would have with a library.

## Dependencies

### C++ Compiler

Yoou need a C++ compiler (for example clang or gcc) to build this project and also to build the generated project

### CMake

To build this project you need CMake. Also to build the generated project you also need CMake.

```bash
sudo apt-get install cmake
```

### SDL2 & SDL2-Image

SDL2 is not a direct dependency (neither is SDL2-Image) but the generated project uses it so to take advantage of the generated project you need to install SDL2 and SDL2-Image.

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev
```

## Installation

```bash
mkdir build bin
cmake -E chdir build/ cmake ..
cmake --build build/
# This is optional to make the application callable from anywhere
sudo cmake --install build/
```

## Usage

```bash
path/to/app/gbgen MyGame
# Or if sudo cmake --install build/ has been run
gbgen MyGame
```

### Output

The output project structure is as follows:

```
MyGame/
|-bin/
|-build/
|-config/
| '-config.h.in
|-include/
| |-BE/
| | |-Cronometer.h
| | |-Game.h
| | |-KeyManager.h
| | |-MouseManager.h
| | |-Random.h
| | '-Time.h
| '-MyGame.h
|-src/
| |-BE/
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

Your game logic should be inside *Scenes*. The generated code already provide *MainMenuScene* and it is a good startup point.

```cpp
#include "MainMenuScene.h"

#include <SDL2/SDL.h>

void MainMenuScene::initialize()
{
    // This method only gets called once before update and render 
    // This is a good place to initialize stuff, such as textures
    // or other resources.
}

void MainMenuScene::shutdown()
{
    // This method only gets calle once after update and render
    // This is a good place to do cleanup, such os closing files 
    // or freeing resources
}

void MainMenuScene::update()
{
	// This gets called once every frame.
    // The game logic should go here.
}

void MainMenuScene::render(SDL_Renderer *renderer)
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
BE::SceneManager::getInstance().pushScene<PauseScene>();

// Pops the current active scene from the stack and the current active
// scene in the next frame will be the next scene in the stack (the 
// shutdown of the scene will be called at the end of the current frame).
BE::SceneManager::getInstance().popScene();

// Pops the current scene from the stack and pushes the new scene (at
// the end of the frame the initialization of the new scene will be
// called and then the shutdown)
BE::SceneManager::getInstance().swap<LevelTwoScene>();
```

For player input you can use *KeyManager* and *MouseManager* classes for input from keyboard and input from mouse respectively.
