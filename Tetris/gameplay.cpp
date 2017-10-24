//
//  gameplay.cpp
//  Tetris
//
//  Created by Termi303 on 24.07.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#include "gameplay.h"

bool Gameplay::isPlayerInMotion() {
    return isPlayerTetrinimoMoving;
}

void Gameplay::increaseScore(int howMuch) {
    score += 50*howMuch*(howMuch+1)*level;
}

void Gameplay::displayBoard() {
    std::cout << "Board:\n";
    for(int alfa = 0; alfa < 20; alfa++) {
        for(int beta = 0; beta < 10; beta++) std::cout << board[alfa][beta] << " ";
        std::cout << "\n";
    }
}

void Gameplay::moveTetrinimoDown(int tetriNumber) {
    if(timeToNextDrop > 0) return;
    if(tetrinimo[tetriNumber].empty()) return;
    
    bool possibleMovement = 1;
    for(int j = 0; j < tetrinimo[tetriNumber].size(); j++) {
        if(isMovingDownPossible(tetrinimo[tetriNumber][j]) == 0) {
            possibleMovement = 0;
            break;
        }
    }
    if(possibleMovement == 0) {
        return;
    }
    isBrickMovedDown = 1;
    for(int j = 0; j < tetrinimo[tetriNumber].size(); j++) {
        board[tetrinimo[tetriNumber][j].takeY()][tetrinimo[tetriNumber][j].takeX()] = -1;
        tetrinimo[tetriNumber][j].moveBrickDown();
    }
    for(int j = 0; j < tetrinimo[tetriNumber].size(); j++) {
        board[tetrinimo[tetriNumber][j].takeY()][tetrinimo[tetriNumber][j].takeX()] = tetriNumber;
    }
    
}

bool Gameplay::MoveBricksDown() {
    if(isPlayerTetrinimoMoving) return 0;
    if(timeToNextDrop > 0) return 1;
    
    isBrickMovedDown = 0;
    for(int i = 0; i < MAX_TETRINIMOS; i++) {
        moveTetrinimoDown(i);
    }
    if(isBrickMovedDown) timeToNextDrop = timeForOneDropInSeconds;
    return isBrickMovedDown;
}

void Gameplay::levelUp() {
    level++;
    if(level <= 20) {
        timeForOneDropInSeconds *= (1.0-difficultyRate);
    }
}

bool Gameplay::hasGameEnded() {
    return gameEnded;
}

void Gameplay::setTetrinimoTab() {
    for(int i = 0; i < TETRINIMO_TAB_SIZE; i++) nextTetrinimo[i] = rand()%NUMBER_OF_TETRINIMO;
}

void Gameplay::setGameStatistics() {
    score = 0;
    level = 1;
    whichTetrinimo = 0;
    isPlayerTetrinimoMoving = 0;
    gameEnded = 0;
    
    linesCleared = 0;
    
    timeForOneDropInSeconds = 0.55;
    timeToNextDrop = timeForOneDropInSeconds;
    timeToNextHorizontalMove = timeForOneHorizontalMoveInSeconds;
    timeToNextPlayerDrop = timeForOneDropInSecondsByPlayer;
    timeToNextRotation = timeForOneRotationInSeconds;
    
    timeForOneDropInSecondsByPlayer = 0.1;
}

void Gameplay::initializeBoard() {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) board[i][j] = EMPTY;
    }
    for(int i = 0; i < MAX_TETRINIMOS; i++) {
        isTetrinimoNumberOccupied[i] = 0;
    }
}

void Gameplay::setScoreAndLevelFonts(sf::Font &normFont, sf::Font &bolFont) {
    preScoreText.setCharacterSize(constGameplayTextSize);
    preLevelText.setCharacterSize(constGameplayTextSize);
    preScoreText.setFont(bolFont);
    preLevelText.setFont(bolFont);
    preScoreText.setString("SCORE");
    preLevelText.setString("LEVEL");
    
    playerScore.setCharacterSize(variableTextSize);
    playerLevel.setCharacterSize(variableTextSize);
    playerScore.setFont(normFont);
    playerLevel.setFont(normFont);
    
    preScoreText.setPosition(BOARD_X+10*BRICK_SIZE+50, BOARD_Y);
    playerScore.setPosition(BOARD_X+10*BRICK_SIZE+115, BOARD_Y+constGameplayTextSize);
    
    preLevelText.setPosition(BOARD_X-190, BOARD_Y);
    playerLevel.setPosition(BOARD_X-125, BOARD_Y+constGameplayTextSize);
}

Gameplay::Gameplay(sf::Font &normFont, sf::Font &bolFont) {
    srand(time(NULL));
    setGameStatistics();
    setTetrinimoTab();
    initializeBoard();
    setScoreAndLevelFonts(normFont, bolFont);
}

Gameplay::~Gameplay() {

}

bool Gameplay::isMovingDownPossible(Brick &brick) {
    if(brick.takeY()+1 < 20 && (board[brick.takeY()+1][brick.takeX()] == -1 || board[brick.takeY()+1][brick.takeX()] == brick.takeNumber() )) return 1;
    return 0;
}

bool Gameplay::isMovingLeftPossible(Brick &brick) {
    if(brick.takeX() > 0 && (board[brick.takeY()][brick.takeX()-1] == -1 || board[brick.takeY()][brick.takeX()-1] == brick.takeNumber() )) return 1;
    return 0;
}

bool Gameplay::isMovingRightPossible(Brick &brick) {
    if(brick.takeX()+1 < 10 && (board[brick.takeY()][brick.takeX()+1] == -1 || board[brick.takeY()][brick.takeX()+1] == brick.takeNumber() )) return 1;
    return 0;
}

void Gameplay::deleteBricks(int rowNumber) {
    for(int i = 0; i < MAX_TETRINIMOS; i++) {
        for(int j = 0; j < tetrinimo[i].size(); j++) {
            if(tetrinimo[i][j].takeY() == rowNumber) {
                tetrinimo[i].erase(tetrinimo[i].begin()+j);
                j--;
            }
        }
        
        if(tetrinimo[i].empty()) {
            isTetrinimoNumberOccupied[i] = 0;
        }
    }
}

int Gameplay::deleteRow(int rowNumber) {
    for(int j = 0; j < 10; j++) {
        if(board[rowNumber][j] == EMPTY) return 0;
    }
    for(int j = 0; j < 10; j++) {
        board[rowNumber][j] = EMPTY;
    }
    deleteBricks(rowNumber);
    
    linesCleared++;
    if(linesCleared%10 == 0) levelUp();
    return 1;
}

bool Gameplay::areBricksNear(Brick &b1, Brick &b2) {
    if(b1.takeX() == b2.takeX()) {
        if(abs(b1.takeY()-b2.takeY()) == 1) return 1;
    } else if(b1.takeY() == b2.takeY()) {
        if(abs(b1.takeX()-b2.takeX()) == 1) return 1;
    }
    return 0;
}

void Gameplay::checkCohesion() {
    for(int i = 0; i < MAX_TETRINIMOS; i++) {
        if(tetrinimo[i].size() == 2) {
            if(!areBricksNear(tetrinimo[i][0], tetrinimo[i][1])) {
                Brick tmp = tetrinimo[i][1];
                int newNumber = 0;
                tetrinimo[i].erase(tetrinimo[i].begin()+1);
                while(isTetrinimoNumberOccupied[newNumber]) newNumber++;
                
                isTetrinimoNumberOccupied[newNumber] = 1;
                tmp.setNumber(newNumber);
                tetrinimo[newNumber].push_back(tmp);
                board[tmp.takeY()][tmp.takeX()] = newNumber;
            }
        } else if(tetrinimo[i].size() == 3) {
            if(areBricksNear(tetrinimo[i][0], tetrinimo[i][1])) {
                if(!areBricksNear(tetrinimo[i][2], tetrinimo[i][0]) && !areBricksNear(tetrinimo[i][2], tetrinimo[i][1])) {
                    Brick tmp = tetrinimo[i][2];
                    int newNumber = 0;
                    tetrinimo[i].erase(tetrinimo[i].begin()+2);
                    while(isTetrinimoNumberOccupied[newNumber]) newNumber++;
                    
                    isTetrinimoNumberOccupied[newNumber] = 1;
                    tmp.setNumber(newNumber);
                    tetrinimo[newNumber].push_back(tmp);
                    board[tmp.takeY()][tmp.takeX()] = newNumber;
                }
            } else if(areBricksNear(tetrinimo[i][0], tetrinimo[i][2])) {
                if(!areBricksNear(tetrinimo[i][1], tetrinimo[i][0]) && !areBricksNear(tetrinimo[i][1], tetrinimo[i][2])) {
                    Brick tmp = tetrinimo[i][1];
                    int newNumber = 0;
                    tetrinimo[i].erase(tetrinimo[i].begin()+1);
                    while(isTetrinimoNumberOccupied[newNumber]) newNumber++;
                    
                    isTetrinimoNumberOccupied[newNumber] = 1;
                    tmp.setNumber(newNumber);
                    tetrinimo[newNumber].push_back(tmp);
                    board[tmp.takeY()][tmp.takeX()] = newNumber;
                }
            } else if(areBricksNear(tetrinimo[i][1], tetrinimo[i][2])) {
                if(!areBricksNear(tetrinimo[i][0], tetrinimo[i][1]) && !areBricksNear(tetrinimo[i][0], tetrinimo[i][2])) {
                    Brick tmp = tetrinimo[i][0];
                    int newNumber = 0;
                    tetrinimo[i].erase(tetrinimo[i].begin()+0);
                    while(isTetrinimoNumberOccupied[newNumber]) newNumber++;
                    
                    isTetrinimoNumberOccupied[newNumber] = 1;
                    tmp.setNumber(newNumber);
                    tetrinimo[newNumber].push_back(tmp);
                    board[tmp.takeY()][tmp.takeX()] = newNumber;
                }
            }
        }
    }
}

void Gameplay::deleteFullRows() {
    int numberOfDeletedRows = 0;
    
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        if(deleteRow(tetrinimo[NumberOfPlayerTetrinimo][j].takeY()) ) {
            numberOfDeletedRows++;
            j--;
        }
    }
    
    increaseScore(numberOfDeletedRows);
    if(numberOfDeletedRows > 0) checkCohesion();
}

void Gameplay::updateTime(float lastTime) {
    timeToNextDrop -= lastTime;
    timeToNextPlayerDrop -= lastTime;
    timeToNextHorizontalMove -= lastTime;
    timeToNextRotation -= lastTime;
}

void Gameplay::movePlayerTetrinimoDown() {
    if(timeToNextDrop > 0) return;
    timeToNextDrop = timeForOneDropInSeconds;
    
    score++;
    
    bool possibleMovement = 1;
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        if(isMovingDownPossible(tetrinimo[NumberOfPlayerTetrinimo][j]) == 0) {
            possibleMovement = 0;
            break;
        }
    }
    if(possibleMovement == 0) {
        isPlayerTetrinimoMoving = 0;
        deleteFullRows();
        return;
    }
    
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = -1;
        tetrinimo[NumberOfPlayerTetrinimo][j].moveBrickDown();
    }
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = NumberOfPlayerTetrinimo;
    }
    
}

void Gameplay::movePlayerTetrinimoDownByPlayer() {
    if(timeToNextPlayerDrop > 0) return;
    timeToNextPlayerDrop = timeForOneDropInSecondsByPlayer;
    timeToNextDrop = timeForOneDropInSeconds;
    
    score += 2;
    
    bool possibleMovement = 1;
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        if(isMovingDownPossible(tetrinimo[NumberOfPlayerTetrinimo][j]) == 0) {
            possibleMovement = 0;
            break;
        }
    }
    if(possibleMovement == 0) {
        isPlayerTetrinimoMoving = 0;
        deleteFullRows();
        return;
    }
    
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = -1;
        tetrinimo[NumberOfPlayerTetrinimo][j].moveBrickDown();
    }
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = NumberOfPlayerTetrinimo;
    }
    
}

void Gameplay::movePlayerTetrinimoLeft() {
    if(timeToNextHorizontalMove > 0 || isPlayerTetrinimoMoving == 0) return;
    timeToNextHorizontalMove = timeForOneHorizontalMoveInSeconds;
    
    bool possibleMovement = 1;
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        if(isMovingLeftPossible(tetrinimo[NumberOfPlayerTetrinimo][j]) == 0) {
            possibleMovement = 0;
            break;
        }
    }
    if(possibleMovement == 0) {
        return;
    }
    
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = -1;
        tetrinimo[NumberOfPlayerTetrinimo][j].moveBrickLeft();
    }
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = NumberOfPlayerTetrinimo;
    }
}

void Gameplay::movePlayerTetrinimoRight() {
    if(timeToNextHorizontalMove > 0 || isPlayerTetrinimoMoving == 0) return;
    timeToNextHorizontalMove = timeForOneHorizontalMoveInSeconds;
    
    bool possibleMovement = 1;
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        if(isMovingRightPossible(tetrinimo[NumberOfPlayerTetrinimo][j]) == 0) {
            possibleMovement = 0;
            break;
        }
    }
    if(possibleMovement == 0) {
        return;
    }
    
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = -1;
        tetrinimo[NumberOfPlayerTetrinimo][j].moveBrickRight();
    }
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        board[tetrinimo[NumberOfPlayerTetrinimo][j].takeY()][tetrinimo[NumberOfPlayerTetrinimo][j].takeX()] = NumberOfPlayerTetrinimo;
    }
}

bool Gameplay::isBrickOutOfBoard(int x, int y) {
    if(x >= 10 || x < 0 || y < 0 || y >= 20) return 1;
    return 0;
}

void Gameplay::rotatePlayerTetrinimo() {
    if(isPlayerTetrinimoMoving == 0 || timeToNextRotation > 0) return;
    
    int min_x = 1e9, min_y = 1e9, height = 0;
    vector<Brick> temporaryTab;
    for(int j = 0; j < tetrinimo[NumberOfPlayerTetrinimo].size(); j++) {
        temporaryTab.push_back(tetrinimo[NumberOfPlayerTetrinimo][j]);
    }
    for(int j = 0; j < temporaryTab.size(); j++) {
        if(temporaryTab[j].takeX() < min_x) min_x = temporaryTab[j].takeX();
        if(temporaryTab[j].takeY() < min_y) min_y = temporaryTab[j].takeY();
        if(temporaryTab[j].takeY() > height) height = temporaryTab[j].takeY();
    }
    height -= min_y;
    for(int j = 0; j < temporaryTab.size(); j++) {
        temporaryTab[j].changePosition( temporaryTab[j].takeX()-min_x , temporaryTab[j].takeY()-min_y);
        temporaryTab[j].changePosition( height - temporaryTab[j].takeY() , temporaryTab[j].takeX());
        temporaryTab[j].changePosition( temporaryTab[j].takeX()+min_x , temporaryTab[j].takeY()+min_y);
        
        if( (board[ temporaryTab[j].takeY() ][ temporaryTab[j].takeX() ] != EMPTY &&
           board[ temporaryTab[j].takeY() ][ temporaryTab[j].takeX() ] != NumberOfPlayerTetrinimo) ||
           isBrickOutOfBoard(temporaryTab[j].takeX(), temporaryTab[j].takeY()) ) {
            return;
        }
    }
    
    timeToNextRotation = timeForOneRotationInSeconds;
    for(int j = 0; j < temporaryTab.size(); j++) {
        board[ tetrinimo[NumberOfPlayerTetrinimo][j].takeY() ][ tetrinimo[NumberOfPlayerTetrinimo][j].takeX() ] = -1;
        tetrinimo[NumberOfPlayerTetrinimo][j].changePosition(temporaryTab[j].takeX(), temporaryTab[j].takeY());
        board[ tetrinimo[NumberOfPlayerTetrinimo][j].takeY() ][ tetrinimo[NumberOfPlayerTetrinimo][j].takeX() ] = NumberOfPlayerTetrinimo;
    }
}

void Gameplay::showScore(sf::RenderWindow &gameWindow) {
    std::string scoreString = "";
    int scoreClone = score;
    while(scoreClone > 0) {
        scoreString = char( (scoreClone%10)+48 ) + scoreString;
        scoreClone /= 10;
    }
    if(score == 0) scoreString = "0";
    
    playerScore.setString(scoreString);
    
    gameWindow.draw(preScoreText);
    gameWindow.draw(playerScore);
}

void Gameplay::showLevel(sf::RenderWindow &gameWindow) {
    std::string levelString = "";
    int levelClone = level;
    while(levelClone > 0) {
        levelString = char( (levelClone%10)+48 ) + levelString;
        levelClone /= 10;
    }
    if(level == 0) levelString = "0";
    
    playerLevel.setString(levelString);
    
    gameWindow.draw(preLevelText);
    gameWindow.draw(playerLevel);
}

void Gameplay::show(sf::RenderWindow &gameWindow) {
    for(int i = 0; i < MAX_TETRINIMOS; i++)
        for(int j = 0; j < tetrinimo[i].size(); j++)
        {
            tetrinimo[i][j].drawBrick(gameWindow);
        }
    showScore(gameWindow);
    showLevel(gameWindow);
}

bool Gameplay::isCollision(int pl_x, int pl_y) {
    for(int i = 0; i < MAX_TETRINIMOS; i++) {
        if(i == NumberOfPlayerTetrinimo) continue;
        for(int j = 0; j < tetrinimo[i].size(); j++) {
            if(tetrinimo[i][j].takeX() == pl_x &&
               tetrinimo[i][j].takeY() == pl_y) return 1;
        }
    }
    return 0;
}

void Gameplay::buildSquare(sf::Texture &brick) {
    Brick pom(brick);
    pom.setBrick(4, 0, sf::Color::Yellow, NumberOfPlayerTetrinimo);
    board[0][4] = NumberOfPlayerTetrinimo;
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    
    pom.setBrick(5, 0, sf::Color::Yellow, NumberOfPlayerTetrinimo);
    board[0][5] = NumberOfPlayerTetrinimo;
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    
    pom.setBrick(4, 1, sf::Color::Yellow, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][4] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 1, sf::Color::Yellow, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][5] = NumberOfPlayerTetrinimo;
}

void Gameplay::buildL(sf::Texture &brick) {
    Brick pom(brick);
    sf::Color orangeColor(255,165,0);
    
    pom.setBrick(4, 0, orangeColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][4] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(4, 1, orangeColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][4] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(4, 2, orangeColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[2][4] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 2, orangeColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[2][5] = NumberOfPlayerTetrinimo;
}

void Gameplay::buildReversedL(sf::Texture &brick) {
    Brick pom(brick);
    sf::Color blueColor(0,0,139);
    
    pom.setBrick(5, 0, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 1, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 2, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[2][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(4, 2, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[2][4] = NumberOfPlayerTetrinimo;
    
}

void Gameplay::buildI(sf::Texture &brick) {
    Brick pom(brick);
    sf::Color blueColor(0,191,255);
    
    pom.setBrick(5, 0, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 1, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 2, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[2][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 3, blueColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[3][5] = NumberOfPlayerTetrinimo;
}

void Gameplay::buildY(sf::Texture &brick) {
    Brick pom(brick);
    sf::Color purpleColor(148,0,211);
    
    pom.setBrick(5, 0, purpleColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 1, purpleColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(4, 1, purpleColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][4] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(6, 1, purpleColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][6] = NumberOfPlayerTetrinimo;
}

void Gameplay::buildZ(sf::Texture &brick) {
    Brick pom(brick);
    sf::Color redColor(220,0,0);
    
    pom.setBrick(4, 0, redColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][4] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 0, redColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 1, redColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(6, 1, redColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][6] = NumberOfPlayerTetrinimo;
}

void Gameplay::buildReversedZ(sf::Texture &brick) {
    Brick pom(brick);
    sf::Color greenColor(0,220,0);
    
    pom.setBrick(6, 0, greenColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][6] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 0, greenColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[0][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(5, 1, greenColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][5] = NumberOfPlayerTetrinimo;
    
    pom.setBrick(4, 1, greenColor, NumberOfPlayerTetrinimo);
    tetrinimo[NumberOfPlayerTetrinimo].push_back(pom);
    board[1][4] = NumberOfPlayerTetrinimo;
}

void Gameplay::createTetrinimo(sf::Texture &brick) {
    if(isPlayerTetrinimoMoving == 1) return;
    
    NumberOfPlayerTetrinimo = 0;
    while(isTetrinimoNumberOccupied[NumberOfPlayerTetrinimo]) NumberOfPlayerTetrinimo++;
    isTetrinimoNumberOccupied[NumberOfPlayerTetrinimo] = 1;
    
    nextTetrinimo[whichTetrinimo++] = rand()%NUMBER_OF_TETRINIMO;
    if(whichTetrinimo == TETRINIMO_TAB_SIZE) whichTetrinimo = 0;
    isPlayerTetrinimoMoving = 1;
    
    switch(nextTetrinimo[whichTetrinimo]) {
        case 0: buildSquare(brick);
            break;
        case 1: buildL(brick);
            break;
        case 2: buildReversedL(brick);
            break;
        case 3: buildI(brick);
            break;                      //BuildY:   *
        case 4: buildY(brick);           //         ***
            break;
        case 5: buildZ(brick);
            break;
        case 6: buildReversedZ(brick);
            break;
    };
    
    tetrinimoType[NumberOfPlayerTetrinimo] = nextTetrinimo[whichTetrinimo];
    for(int alfa = 0; alfa < tetrinimo[NumberOfPlayerTetrinimo].size(); alfa++) {
        if(isCollision(tetrinimo[NumberOfPlayerTetrinimo][alfa].takeX(), tetrinimo[NumberOfPlayerTetrinimo][alfa].takeY())) {
            gameEnded = 1;
            return;
        }
    }
    
    timeToNextDrop = timeForOneDropInSeconds;
    timeToNextPlayerDrop = timeForOneDropInSecondsByPlayer;
}