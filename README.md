# Game Boilerplate Generator

Simple application used to create boilerplate for SDL2 with key input handler

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
