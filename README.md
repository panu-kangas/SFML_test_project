# Overview  

Snake_SFML is a simple game written in C++. It's based on the classic snake-game, but has additional features developed by me.  

The program utilizes the SFML (Simple and Fast Multimedia Library) and uses CMake as it's build system.  
It should work on macOS (tested), Linux (tested) and on Windows using Visual Studio -program (not tested). 

This is my first ever SFML project and also my first C++ game, so the code might be a bit funky 😁  

I really hope you enjoy the game! 😊 

# Installation

Instructions on how to use the game.

## Prerequisites

1. You need to install **CMake** and **Git** in order to be able to compile this project.  
2. On Windows, you need the Visual Studio -program.  
3. If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
    ```
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```

## Compilation instructions

Run the following commands in your terminal:

1. ```git clone https://github.com/panu-kangas/Snake_SFML.git && cd Snake_SFML```  
2. ```cmake -B build```  
3. ```cmake --build build```
4. ```./snake_2d```

# About the game

As mentioned earlier, this game is a snake-based 2D-game. 
The player controls a snake-character, that moves constantly on the map. 

### Controls

ARROW KEYS & ENTER - Navigate the start menu 
WASD - Change snake's moving direction in game 
SPACE - Use snake's boost speed 

### Goal of the game
  
Collect all the apples on the map. Once you reach the last apple, you win 😎 
Watch out for the nasty towers though, because they are trying to shoot you!

### Losing conditions

If you hit a wall, a tower or one of the arrows fired by the tower, you lose 🙁 

