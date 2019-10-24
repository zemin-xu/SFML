//
//  Player.hpp
//  SFML
//
//  Created by ZEMIN on 17/10/2019.
//  Copyright © 2019 ZEMIN. All rights reserved.
//

#include "LIB.hpp"

#ifndef Player_hpp
#define Player_hpp

class Player : public Creature
{
public:
    
    
protected:
    int weaponPoint;
    
    
public:
    
    Player();
    Player(int x, int y, int length, int height, sf::Texture *texture, int numHorizontal, int numVertical, int _kind);
    
    int GetWeaponPoint() {return (weaponPoint); }

    //void DetectCollision(Map map, vector<Collectable> &collectables, vector<Movable> &movables, const float deltaTime);
    
    
   
    // reaction when meeting a collision
    
    //void Collision(vector<Collectable> &collectables);
    //void Collision(Map map, vector<Movable> &movables, const float deltaTime);
    
    virtual void Move(const float deltaTime);
    
    void UpdateState();
    void Update(const float deltaTime, vector<Element> &obstacles, vector<Collectable> &collectables, vector<Movable> &movables);
    void Render(sf::RenderWindow &window);
    

};


#endif /* Player_hpp */
