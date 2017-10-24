//
//  brick.h
//  Tetris
//
//  Created by Termi303 on 24.07.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#ifndef __Tetris__brick__
#define __Tetris__brick__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"

class Brick {
private:
    int x;
    int y;
    int number;
    
    sf::Sprite brickSprite;
    
public:
    Brick(sf::Texture &kost);
    ~Brick();
    void drawBrick(sf::RenderWindow &gameWindow);
    void changePosition(int newX, int newY);
    
    void setBrick(int m_x, int m_y, sf::Color newColor, int newNumber);
    void setBrickColor(sf::Color &newBrickColor);
    void setNumber(int newNumber);
    
    int takeX();
    int takeY();
    int takeNumber();
    
    void moveBrickDown();
    void moveBrickLeft();
    void moveBrickRight();
};

#endif /* defined(__Tetris__brick__) */
