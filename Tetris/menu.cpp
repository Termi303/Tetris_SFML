//
//  menu.cpp
//  Tetris
//
//  Created by Termi303 on 23.07.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#include "menu.h"

void Menu::setOptionsFonts(int posY, sf::Font &normFont, sf::Font &bolFont) {
    for(int i = 0; i < 3; i++) {
        optionsMenu[i].setFont(normFont);
        optionsMenu[i].setCharacterSize(optionsSize);
        pointed[i] = 0;
    }
     if(posY >= startOptionsY && posY < startOptionsY + OptionsDiffY*4/5) {
         optionsMenu[0].setFont(bolFont);
         pointed[0] = 1;
         optionsMenu[0].setCharacterSize(pointedSize);
     }
     if(posY >= startOptionsY + OptionsDiffY && posY < startOptionsY + OptionsDiffY*2) {
         optionsMenu[1].setFont(bolFont);
         pointed[1] = 1;
         optionsMenu[1].setCharacterSize(pointedSize);
     }
     if(posY >= startOptionsY + OptionsDiffY*2 && posY < startOptionsY + OptionsDiffY*3) {
         optionsMenu[2].setFont(bolFont);
         pointed[2] = 1;
         optionsMenu[2].setCharacterSize(pointedSize);
     }
}

void Menu::show(sf::RenderWindow &gameWindow) {
    gameWindow.draw(title);
    for(int i = 0; i < 3; i++) gameWindow.draw(optionsMenu[i]);
}

Menu::Menu(sf::Font &normFont, sf::Font &bolFont) {
    createTitle(bolFont);
    createOptionsMenu(normFont);
    
    setTitlePosition();
    setOptionsPosition();
}

Menu::~Menu() {

}

void Menu::setTitlePosition() {
    title.setPosition(titleX, titleY);
}

void Menu::setOptionsPosition() {
    optionsMenu[0].setPosition(430, startOptionsY);
    optionsMenu[1].setPosition(250, startOptionsY+OptionsDiffY);
    optionsMenu[2].setPosition(440, startOptionsY+2*OptionsDiffY);
}

void Menu::createTitle(sf::Font &bolFont) {
    sf::Text pom;
    pom.setFont(bolFont);
    
    title = pom;
    title.setCharacterSize(titleSize);
    title.setString("TETRIS");
}

void Menu::createOptionsMenu(sf::Font &normFont) {
    sf::Text pom;
    pom.setFont(normFont);
    pom.setCharacterSize(optionsSize);
    
    pom.setString("PLAY");
    optionsMenu.push_back(pom);
    
    pom.setString("LEADERBOARD");
    optionsMenu.push_back(pom);
    
    pom.setString("QUIT");
    optionsMenu.push_back(pom);
    
}