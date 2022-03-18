# Game Boilerplate Generator

Simple application used to create boilerplate for [SDL2](https://www.libsdl.org/download-2.0.php).
This project will generate all files needed to build and run an SDL2 project.

## Dependencies 
#### C++ Compiler
Yoou need a C++ compiler (for example clang or gcc) to build this project and also to build the generated project

#### CMake
To build this project you need CMake. Also to build the generated project you also need CMake.
```bash
sudo apt-get install cmake
```

#### SDL2
SDL2 is not a direct dependency but the generated project uses it so to take advantage of the generated project you need to install SDL2
```bash
sudo apt-get install libsdl2-dev
```

## installation
```bash
mkdir build
mkdir bin
cmake -E chdir build/ cmake ..
cmake --build build/
# This is optional to make the application callable from anywhere
sudo cmake --install build/
```

## Usage
```bash
path/to/app/gbgen ProjectNameGoesHere
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

### Generated files
#### Game
This is the core class that initializes and shutdowns the SDL2, manages the main loop and processes SDL2 events. Your **MyGame** class inherite from **Game** class (**ATTENTION:** It uses [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)). 

Usage:
```cpp
#include "BE/Game.h"

#include <SDL2/SDL.h>

// Minimum required class definition to create a game
class MyGame final : public BE::Game<MyGame>
{
public:
  MyGame() = default;
  MyGame() = default;
  
private:
  friend class BE::Game<MyGame>;
  
  // All these methods bellow need to be implemented otherwise it wont compile
  void initialize() 
  {
    // Initialization stuff goes here
  }
  
  void shutdown()
  {
    // Shutdown stuff goes here
  }
  
  void update()
  {
    // This method is called every frame to update the game state
  }
  
  void render(SDL_Renderer *renderer)
  {
    // This method is called to render the game
  }
};

// SDL2 requires that you declare your main function with argc and argv
int main(int argc, char *argv[])
{
  MyGame().run();
  
  return 0;
}

```

#### Time
This class caps the frame rate (that is defined in _config/config.h.in_ file) and is used to obtain the delta time (time passed since last update call). This is needed to make your game [framerate-independent](https://gameprogrammingpatterns.com/game-loop.html).

Usage:
```cpp
#include "BE/Time.h"

// ...

void MyGame::update()
{
  float deltaTime = BE::Time::getDeltaTime();
  
  // ..
  
  // Make player fall
  player->position.x += 9.81f * deltaTime;
}


```
