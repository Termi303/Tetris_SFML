# Tetris_SFML
Tetris implemented during 2016 holidays, using C++ and SFML engine.
The game is playable. However, Leaderboard section is not implemented and there are no sound effects.

The project was developed in Mac OS X (Xcode).

All images and programs are created by me (I used GIMP).
C++ programs and images are in Tetris directory.

Short description of programs:

- constants.h - There are constants, which are used in other files.
- game.h and game.cpp - These programs are responsible for starting the app (loading files, initializing object Game), displaying right section of app, and there is game loop.
- gameplay.h and gameplay.cpp - Main part of this project. Here are all functions needed to get the game going: building, dropping and rotating tetrinimos; deleting rows; showing score and level; 
- brick.h and brick.cpp - These programs are responsible for graphical operations on bricks, particularly on sprites - move, choose colour. Also, there are functions takeX, takeY, takeNumber.
- menu.h and menu.cpp - These programs implement details of menu section: choosing font, sizes, etc.
- main.cpp - Just start the program, create Game object and start the game.

Author: Igor Dolecki (Termi303)
