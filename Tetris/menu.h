//
//  menu.h
//  Tetris
//
//  Created by Termi303 on 23.07.2016.
//  Copyright (c) 2016 Termi303. All rights reserved.
//

#ifndef __Tetris__menu__
#define __Tetris__menu__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;

class Menu {
private:
    sf::Text title;
    vector<sf::Text> optionsMenu;
    
    static const int titleX = 305;
    static const int titleY = 0;
    
    static const int startOptionsY = 250;
    static const int OptionsDiffY = 150;
    
    static const int optionsSize = 120;
    static const int pointedSize = 130;
    static const int titleSize = 200;
    
    void setSizes();
    void createTitle(sf::Font &bolFont);
    void createOptionsMenu(sf::Font &normFont);
    
    void setTitlePosition();
    void setOptionsPosition();
    
public:
    Menu(sf::Font &normFont, sf::Font &bolFont);
    ~Menu();
    
    bool pointed[3];
    
    void show(sf::RenderWindow &gameWindow);
    void setOptionsFonts(int wspolY, sf::Font &normFont, sf::Font &bolFont);
};



#endif /* defined(__Tetris__menu__) */
