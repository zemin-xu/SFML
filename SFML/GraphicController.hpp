//
//  GraphicController.hpp
//  SFML
//
//  Created by ZEMIN on 15/10/2019.
//  Copyright © 2019 ZEMIN. All rights reserved.
//

#ifndef GraphicController_hpp
#define GraphicController_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Element.hpp"

using namespace std;

class GraphicController
{
private:

public:
    
    sf::Texture texturePlayer;
    sf::Texture textureEnemy;
    sf::Texture textureBG;
    sf::Texture textureObstacle;
    sf::Texture textureCollectable;
    
    static const int LENGTH_UNIT = 64;
    static const int HEIGHT_UNIT = 64;
    
    static const int ANIM_PLAYER_NUM_HORIZONTAL = 10;
    static const int ANIM_PLAYER_NUM_VERTICAL = 8;
    
    vector<Element> elements;
    
    Player player;
    
    GraphicController();
    
    void ReadTextureFile();
    void Update();
    void Render(sf::RenderWindow &window);
};

class InputController
{
public:
    InputController();
    
    void UpdateInput(Player &player);
};

    

#endif /* GraphicController_hpp */