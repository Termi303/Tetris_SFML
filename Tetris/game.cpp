//
//  game.cpp
//  Tetris
//
//  Created by Termi303 on 20.06.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#include "game.h"


Game::Game() {
    gameWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tetris", sf::Style::Default);
    gameWindow.setVerticalSyncEnabled(true);
    criticalError = 0;
    
    loadFiles();
    
    background.setTexture(backgroundFile);
    
    board.setTexture(boardFile);
    board.setPosition(BOARD_X-5, BOARD_Y-5);
    
    section = MENU_OPENED;
    
    brick.setSmooth(true);
    
    menu = new Menu(normalFont, boldFont);
}

Game::~Game() {
    
}

void Game::loadFiles() {
    if(!normalFont.loadFromFile(resourcePath() + "SF Atarian System.ttf")) {
        criticalError = 1;
    }
    if(!boldFont.loadFromFile(resourcePath() + "SF Atarian System Bold.ttf")) {
        criticalError = 1;
    }
    if(!brick.loadFromFile(resourcePath() + "brick.png")) {
        criticalError = 1;
    }
    if(!backgroundFile.loadFromFile(resourcePath() + "background.png")) {
        criticalError = 1;
    }
    if(!boardFile.loadFromFile(resourcePath() + "board.png")) {
        criticalError = 1;
    }
}

void Game::displayMenu() {
    while(gameWindow.isOpen() && section == 0) {
        
        // Process events
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                gameWindow.close();
            }
        }
        
        int wspolY = sf::Mouse::getPosition(gameWindow).y;
        menu->setOptionsFonts(wspolY, normalFont, boldFont);
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(menu->pointed[0] == 1) {
                section = GAMEPLAY_OPENED;
                gameplay = new Gameplay(normalFont, boldFont);
            } else if(menu->pointed[1] == 1) {
                section = LEADERBOARD_OPENED;
            } else if(menu->pointed[2] == 1) {
                gameWindow.close();
                break;
            }
        }
        
        gameWindow.clear();
        gameWindow.draw(background);
        menu->show(gameWindow);
        gameWindow.display();
    }
}

void Game::displayGameplay() {
    while(gameWindow.isOpen() && section == 1) {
        //Escape and closing the window
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
                delete gameplay;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                section = MENU_OPENED;
                delete gameplay;
            }
        }
        
        if(gameplay->hasGameEnded()) {
            section = MENU_OPENED;
            break;
        }
        timeInLastFrame = clock.restart().asSeconds();
        gameplay->updateTime(timeInLastFrame);
        
        if(gameplay->MoveBricksDown() == 1) {
            //Wait
        } else {
        
        if(!gameplay->isPlayerInMotion()) {
            int howManyRows = 0;
            for(int row = 0; row < 20; row++) {
                howManyRows += gameplay->deleteRow(row);
            }
            gameplay->increaseScore(howManyRows);
            if(!howManyRows) gameplay->createTetrinimo(brick);
            else continue;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            gameplay->rotatePlayerTetrinimo();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            gameplay->movePlayerTetrinimoLeft();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            gameplay->movePlayerTetrinimoRight();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            gameplay->movePlayerTetrinimoDownByPlayer();
        } else gameplay->movePlayerTetrinimoDown();
        
        }
            
        gameWindow.clear();
        gameWindow.draw(background);
        
        gameWindow.draw(board);
        gameplay->show(gameWindow);
        
        gameWindow.display();
    }
}

void Game::displayLeaderboard() {
    while(gameWindow.isOpen() && section == 2) {
        //Escape and closing the window
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                section = MENU_OPENED;
            }
        }
        
        gameWindow.clear();
        
        gameWindow.draw(background);
        gameWindow.display();
    }
}

void Game::gameLoop() {
    while(gameWindow.isOpen() && criticalError == 0) {
        switch(section) {
            case MENU_OPENED: displayMenu();
                break;
            case GAMEPLAY_OPENED: displayGameplay();
                break;
            case LEADERBOARD_OPENED: displayLeaderboard();
                break;
        }
    }
}

void Game::start() {
    gameLoop();
    if(gameWindow.isOpen()) gameWindow.close();
}
