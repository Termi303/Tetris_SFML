//
//  game.h
//  Tetris
//
//  Created by Termi303 on 20.06.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//
#include "menu.h"
#include "gameplay.h"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"


#ifndef Tetris_game_h
#define Tetris_game_h

class Game {
private:
    void loadFiles();
    void gameLoop();

protected:
    
    int section; //0 - menu; 1 - graj; 2 - tabela liderów
    
    sf::RenderWindow gameWindow;
    sf::Texture brick;
    sf::Texture backgroundFile;
    sf::Texture boardFile;
    
    sf::Sprite background;
    sf::Sprite board;
    
    sf::Font normalFont;
    sf::Font boldFont;
    sf::Text points;
    
    sf::Clock clock;
    float timeInLastFrame;
    
    Menu *menu;
    Gameplay *gameplay;
    
    void displayMenu();
    void displayGameplay();
    void displayLeaderboard();
    
    bool criticalError;
    
    
public:
    Game();
    ~Game();
    void start();
};

#endif
