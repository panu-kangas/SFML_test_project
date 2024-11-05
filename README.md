# Overview  

Snake_SFML is a simple game written in C++. It's based on the classic snake-game, but has additional features developed by me.  

The program utilizes the SFML (Simple and Fast Multimedia Library) and uses CMake as it's build system. It should work on macOS (tested), Linux (tested) and on Windows using Visual Studio -program (tested).  
 
NOTE:  
If you are using Windows, you might need to move the executable file (called "snake_2d") from the out/build -folder to the root of the repository. I'll fix this later, sorry for the inconvenience 🙈

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

As mentioned earlier, this game is a snake-based 2D-game. The player controls a snake-character, that moves constantly on the map. At the moment the game has 3 built-in levels you can play.  
 
Additonally, you can also give one map-file as an argument to the program  
(e.g. ```./snake_2d PATH_TO_MY_MAP_FILE```)  
and it will then use it instead. So if you want to create your own map and test it out, go ahead and try it 🙂  
You can look into the ```maps```folder for example maps, but they are just basic text files with the map layout written in simple characters.  
(0 = grass, 1 = wall, T = Tower, C = Collectible, S = Snake)

### Game controls

ARROW KEYS & ENTER - Navigate the start menu  
WASD - Change snake's moving direction in game  
SPACE - Use snake's boost speed  
ESC - Exit the game

### Goal of the game
  
Collect all the apples on the map. Once you reach the last apple, you win 😎 
Watch out for the nasty towers though, because they are trying to shoot you!

### Losing conditions

If you hit a wall, a tower or one of the arrows fired by the tower, you lose 🙁

# Future develompent ideas

I want to develop this game further once I have more time on my hands. I will fix/create at least the following things:  

1. Fixing snake's hitbox (it's now rectangular, even when the snake sprite is round... very annoying, sorry about that 🙈)
2. Adding destructable objects and bombs. I want to add a game mechanic where the snake can collect bombs that are found in the map, and then use them to destroy obstacles from it's path. I think this would make the game more fun! 🙂
3. Adding a score system. I'm thinking of either a time based system (the faster you collect all the apples, the greater score you get) or a game speed based system (in the beginning of the level, player can choose a game speed. The greater the speed, the greater the score for collecting all of the apples).

