//
//  gameplay.h
//  Tetris
//
//  Created by Termi303 on 24.07.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#ifndef __Tetris__gameplay__
#define __Tetris__gameplay__

#include "brick.h"
#include <ctime>
#include "constants.h"

using std::vector;
using std::set;

class Gameplay {
private:
    
    bool gameEnded;
    
    int score;
    int level;
    int linesCleared;
    
    float timeForOneDropInSeconds;
    float timeForOneDropInSecondsByPlayer;
    float timeToNextDrop;
    float timeToNextPlayerDrop;
    float timeToNextHorizontalMove;
    float timeToNextRotation;
    
    sf::Text preScoreText;
    sf::Text preLevelText;
    
    sf::Text playerScore;
    sf::Text playerLevel;
    
    
    int board[20][10];
    bool contact[MAX_TETRINIMOS][MAX_TETRINIMOS];
    void initializeBoard();
    
    bool isPlayerTetrinimoMoving;
    int NumberOfPlayerTetrinimo;
    int whichTetrinimo;
    
    void moveTetrinimoDown(int tetriNumber);
    
    int tetrinimoType[MAX_TETRINIMOS];
    int nextTetrinimo[TETRINIMO_TAB_SIZE];
    vector<Brick> tetrinimo[MAX_TETRINIMOS];
    bool isTetrinimoNumberOccupied[MAX_TETRINIMOS];
    
    void setGameStatistics();
    void setTetrinimoTab();
    
    void buildSquare(sf::Texture &kost);
    void buildL(sf::Texture &kost);
    void buildReversedL(sf::Texture &kost);
    void buildI(sf::Texture &kost);
    void buildY(sf::Texture &kost);
    void buildZ(sf::Texture &kost);
    void buildReversedZ(sf::Texture &kost);
    bool isCollision(int pl_x, int pl_y);
    
    
    void deleteFullRows();
    void checkCohesion();
    bool areBricksNear(Brick &b1, Brick &b2);
    void deleteBricks(int rowNumber);
    
    bool isMovingDownPossible(Brick &brick);
    bool isMovingLeftPossible(Brick &brick);
    bool isMovingRightPossible(Brick &brick);
    bool isBrickOutOfBoard(int x, int y);
    
    void setScoreAndLevelFonts(sf::Font &normFont, sf::Font &bolFont);
    void showScore(sf::RenderWindow &gameWindow);
    void showLevel(sf::RenderWindow &gameWindow);
    
    void levelUp();
    bool isBrickMovedDown;
    
public:
    Gameplay(sf::Font &normFont, sf::Font &bolFont);
    ~Gameplay();
    void show(sf::RenderWindow &gameWindow);
    void createTetrinimo(sf::Texture &kost);
    
    void movePlayerTetrinimoDown();
    void movePlayerTetrinimoDownByPlayer();
    
    void movePlayerTetrinimoLeft();
    void movePlayerTetrinimoRight();
    void rotatePlayerTetrinimo();
    bool isPlayerInMotion();
    
    void updateTime(float lastTime);
    bool hasGameEnded();
    bool MoveBricksDown();
    bool isDeletePossible();
    
    void displayBoard();
    int deleteRow(int rowNumber);
    void increaseScore(int howMuch);
};

#endif /* defined(__Tetris__gameplay__) */
