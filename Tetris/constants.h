//
//  constants.h
//  Tetris
//
//  Created by Termi303 on 20.06.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#ifndef Tetris_constants_h
#define Tetris_constants_h

#include <iostream>
#include <cmath>

const int BRICK_SIZE = 30;
const int LEFT = -1;
const int RIGHT = 1;
const int startBrickX = 362;
const int startBrickY = 84;
const int TETRINIMO_TAB_SIZE = 20;
const int NUMBER_OF_TETRINIMO = 7;
const int MAX_TETRINIMOS = 250;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int constGameplayTextSize = 70;
const int variableTextSize = constGameplayTextSize*4/5;

const int MENU_OPENED = 0;
const int GAMEPLAY_OPENED = 1;
const int LEADERBOARD_OPENED = 2;

const int BOARD_X = 362;
const int BOARD_Y = 84;
const int EMPTY = -1;

const float timeForOneHorizontalMoveInSeconds = 0.1;
const float timeForOneRotationInSeconds = 0.2;
const float difficultyRate = 0.2;


#endif
