//
//  brick.cpp
//  Tetris
//
//  Created by Termi303 on 24.07.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#include "brick.h"

void Brick::setBrick(int m_x, int m_y, sf::Color newColor, int newNumber) {
    x = m_x;
    y = m_y;
    number = newNumber;
    brickSprite.setColor(newColor);
    brickSprite.setPosition(BOARD_X + BRICK_SIZE*x, BOARD_Y + BRICK_SIZE*y);
}

void Brick::setNumber(int newNumber) {
    number = newNumber;
}

Brick::Brick(sf::Texture &kost) {
    brickSprite.setTexture(kost);
}

Brick::~Brick() {

}

void Brick::changePosition(int newX, int newY) {
    brickSprite.move( (newX-x)*BRICK_SIZE, (newY-y)*BRICK_SIZE );
    x = newX;
    y = newY;
}

void Brick::drawBrick(sf::RenderWindow &gameWindow) {
    gameWindow.draw(brickSprite);
}

void Brick::moveBrickDown() {
    y++;
    brickSprite.move(0, BRICK_SIZE);
}

void Brick::moveBrickLeft() {
    x--;
    brickSprite.move(-BRICK_SIZE, 0);
}

void Brick::moveBrickRight() {
    x++;
    brickSprite.move(BRICK_SIZE, 0);
}

void Brick::setBrickColor(sf::Color &newBrickColor) {
    brickSprite.setColor(newBrickColor);
}

int Brick::takeNumber() {
    return number;
}

int Brick::takeY() {
    return y;
}

int Brick::takeX() {
    return x;
}