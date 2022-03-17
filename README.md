# Game Boilerplate Generator

Simple application used to create boilerplate for [SDL2](https://www.libsdl.org/download-2.0.php) with key input handler

## Dependencies 
#### C++ Compiler
This project is build using C++ so a c++ is required (for example clang or gcc)


#### CMake
Cmake is used to manage the project
```bash
sudo apt-get install cmake
```

#### SDL2
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
gbgen ProjectNameGoesHere
```

### Output
The output project structure is as follows:
```
ProjectNameGoesHere/
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
| '-ProjectNameGoesHere.h
|-src/
| |-BE/
| | |-Cronometer.cpp
| | |-Game.cpp
| | |-KeyManager.cpp
| | |-MouseManager.cpp
| | |-Random.cpp
| | '-Time.cpp
| |-ProjectNameGoesHere.cpp
| '-main.cpp
'-CMakeLists.txt
```
