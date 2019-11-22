//
//  Level.cpp
//  SFML
//
//  Created by ZEMIN on 24/10/2019.
//  Copyright © 2019 ZEMIN. All rights reserved.

// Level state :
// All the list of objects, textures as well as level maps will exist here.
// All the corresponding initilization and update of list and objects will be here.
// There are also the variables that are not supposed to be reinitialized like
// the num of playerLife and that of playerProjectile, UI, etc.

#include "LIB.hpp"

Level::Level()
{
    
}

Level::Level(int _currentLevel)
{
    ReadTextureFile();
    InitLevel(_currentLevel);
    playerLife = 5;
    playerProjectileNum = 0;
    isEnemyAwake = false;
}


void Level::ReadTextureFile()
{
    if (!font.loadFromFile("Sources/karma_future.ttf"))
        return ;
    if (!bgMusic.openFromFile("Sources/Sounds/ingame.ogg"))
        return ;
    if (!winMusic.openFromFile("Sources/Sounds/win.ogg"))
        return ;
    if (!loseMusic.openFromFile("Sources/Sounds/gameover.ogg"))
        return ;
    
    
    if (!texturePlayer.loadFromFile("Sources/player.png"))
        return ;
    if (!textureEnemyStaticSleep.loadFromFile("Sources/enemy_static_sleep.png"))
        return ;
    if (!textureEnemyStaticAwake.loadFromFile("Sources/enemy_static_awake.png"))
        return ;
    if (!textureEgg.loadFromFile("Sources/mushroom3.png"))
        return ;
    if (!textureObstacleEnemy.loadFromFile("Sources/ghost.png"))
        return ;
    
    if (!textureBackground.loadFromFile("Sources/background.png"))
    return ;
    if (!textureBG2.loadFromFile("Sources/bridge.png"))
        return ;
    if (!textureClosedKeyBox.loadFromFile("Sources/keybox_closed.png"))
        return ;
    if (!textureOuterWall.loadFromFile("Sources/wall.png"))
        return ;
    if (!textureClosedDoor.loadFromFile("Sources/door_closed.png"))
        return ;
    if (!textureOpenDoor.loadFromFile("Sources/door_open.png"))
        return ;
    if (!textureObstacle1.loadFromFile("Sources/tree1.png"))
        return ;
    if (!textureObstacle2.loadFromFile("Sources/tree2.png"))
        return ;
    if (!textureObstacle3.loadFromFile("Sources/head.png"))
        return ;
    if (!textureCollectable.loadFromFile("Sources/mushroom1.png"))
        return ;
    if (!textureCollectable2.loadFromFile("Sources/mushroom2.png"))
        return ;
    if (!textureMovable.loadFromFile("Sources/movable.png"))
        return ;
    if (!textureUI.loadFromFile("Sources/mushroom2.png"))
        return ;
}

void Level::UpdateCurrentMap()
{
    currentMap.clear();
    heartLeft = 0;
    
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            coord a;
            a.x = j;
            a.y = i;
            if (currentLevel == 1)
                a.type = level1[i][j];
            else if (currentLevel == 2)
                a.type = level2[i][j];
            else if (currentLevel == 3)
                a.type = level3[i][j];
            currentMap.push_back(a);
        }
    }
}

void Level::InitLevel(int level)
{
    currentLevel = level;
    heartLeft = 0;
    UpdateCurrentMap();
    
    // the collectable vector and enemy vector should not be clear because it is clean already during running
    if (eggs.size() > 0)
        eggs.clear();
    background.clear();
    obstacles.clear();
    triggers.clear();
    
    /* text init */
    title.setFont(font);
    title.setString("LOLO");
    title.setCharacterSize(24);
    title.setPosition(14.2f * LIB::LENGTH_UNIT, 2 * LIB::HEIGHT_UNIT);
    
    textLife.setFont(font);
    textLife.setCharacterSize(24);
    textLife.setPosition(15.2f * LIB::LENGTH_UNIT, 4.0f * LIB::HEIGHT_UNIT);
    
    textWeapon.setFont(font);
    textWeapon.setCharacterSize(24);
    textWeapon.setPosition(15.2f * LIB::LENGTH_UNIT, 5.5f * LIB::HEIGHT_UNIT);
    
    uiLife = Element(14.0f * LIB::LENGTH_UNIT, 4 * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &texturePlayer, 4, 4, 11);
    uiWeapon = Element(14.0f * LIB::LENGTH_UNIT, 5.5f * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureUI, 1,1, 11);
    
    
    playerProjectile = Projectile(0,0, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureCollectable2, 1, 1, 22);
    
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            
            // background
            if(j >= 1 && j < 14)
            {
                
                Element backgroundUnit;
                backgroundUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureBackground, 5, 1, 11);
                background.push_back(backgroundUnit);
                
                if (currentMap[i * 16 + j].type == 12)
                {
                    backgroundUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureBG2, 1, 1, 11);
                    background.push_back(backgroundUnit);
                }
            }
            
            // obstacles
            if (currentMap[i * 16 + j].type / 10 == 2 || currentMap[i * 16 + j].type == 61)
            {
                Element obstacleUnit;
                if (currentMap[i * 16 + j].type == 22)
                    obstacleUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureOuterWall, 3, 1, 22);
                else if (currentMap[i * 16 + j].type == 21)
                    obstacleUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureObstacle1,1,1, 21);
                else if (currentMap[i * 16 + j].type == 23)
                    obstacleUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureObstacle2,1,1, 23);
                else if (currentMap[i * 16 + j].type == 25)
                    obstacleUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureObstacle3, 3, 1, 25);
                else if (currentMap[i * 16 + j].type == 26)
                obstacleUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureObstacleEnemy, LIB::ANIM_ENEMY1_NUM_HORIZONTAL, LIB::ANIM_ENEMY1_NUM_VERTICAL, 26);
                
                else if (currentMap[i * 16 + j].type == 27)
                    obstacleUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureEnemyStaticSleep , 1, 1, 27);
                else if (currentMap[i * 16 + j].type == 61)
                {
                    obstacleUnit = Element(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureClosedDoor, 1, 1, 61);
                }
                
                obstacles.push_back(obstacleUnit);
            }
            
            else if (currentMap[i * 16 + j].type / 10 == 3)
            {
                Collectable collectableUnit;
                if (currentMap[i * 16 + j].type == 31)
                {
                    collectableUnit = Collectable(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureCollectable ,1,1, 31);
                    heartLeft++;
                }
                if (currentMap[i * 16 + j].type == 32)
                {
                    collectableUnit = Collectable(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureCollectable2, 1, 1, 32);
                }
                collectables.push_back(collectableUnit);
            }
            
            
            // movable
            else if(currentMap[i * 16 + j].type == 41)
            {
                Movable movableUnit(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureMovable ,1,1, 41);
                movables.push_back(movableUnit);
            }
            
            // enemy
            else if(currentMap[i * 16 + j].type / 10 == 5)
            {
                
            }
            
            
            if(currentMap[i * 16 + j].type / 10 == 6)
            {
                Trigger triggerUnit;
                
                if (currentMap[i * 16 + j].type == 61)
                    triggerUnit = Trigger(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureOpenDoor, 1, 1, 61);
                
                else if (currentMap[i * 16 + j].type == 62)
                {
                    triggerUnit = Trigger(j * LIB::LENGTH_UNIT, i * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureClosedKeyBox, 1, 1, 62);
                    triggerUnit.SetIsTriggerActive(false);
                }
                triggers.push_back(triggerUnit);
            }
            
            else if(currentMap[i * 16 + j].type == 71)
                player = Player(j * LIB::LENGTH_UNIT, i * LIB::LENGTH_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &texturePlayer, LIB::ANIM_PLAYER_NUM_HORIZONTAL, LIB::ANIM_PLAYER_NUM_VERTICAL, 71);
        }
    }
}


void Level::UpdateHeartLeft()
{
    
    heartLeft--;
    if (heartLeft <= 0)
        HeartCollected();
}

void Level::AwakenEnemy()
{
    for(int i = 0; i < obstacles.size(); i++)
    {
        
        if (obstacles[i].kind == 27)
        {
            StaticEnemy staticEnemyUnit(obstacles[i].centerX - LIB::LENGTH_UNIT / 2, obstacles[i].centerY - LIB::LENGTH_UNIT / 2, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureEnemyStaticAwake, LIB::ANIM_ENEMY1_NUM_HORIZONTAL, LIB::ANIM_ENEMY1_NUM_VERTICAL, 28);
            obstacles.push_back(staticEnemyUnit);
            obstacles.erase(obstacles.begin() + i);
        }
    }
}

void Level::UpdatePlayerProjectileNum()
{
    playerProjectileNum++;
}


// when all the hearts are collected
void Level::HeartCollected()
{
    for(int i = 0; i < triggers.size(); i++)
        if (triggers[i].kind == 62)
        {
            triggers[i].shape.setFillColor(sf::Color::Red);
            triggers[i].SetIsTriggerActive(true);
        }
}

void Level::CleanLevelEnemy()
{
    enemies.clear();
    movables.clear();
    eggs.clear();
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles[i].kind == 26 || obstacles[i].kind == 28)
            obstacles.erase(obstacles.begin() + i);
    }
}


void Level::Update(const float deltaTime)
{
    player.Update(deltaTime, obstacles, collectables, movables, triggers ,eggs);
    
    playerProjectile.Update(deltaTime, obstacles, enemies, eggs, *this);
    
    // check the moment to awaken the enemies in sleep
    if (heartLeft <= 1 && !isEnemyAwake)
    {
        cout<< "work";
        AwakenEnemy();
        isEnemyAwake = true;
    }
    
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Update(deltaTime, obstacles, collectables, movables, triggers, eggs, &player);
    }
    
    // update of obstacle ememies and static enemies
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles[i].kind == 26)
        {
            ObstacleEnemy* p = (ObstacleEnemy*)&obstacles[i];
            p->Update(&player, deltaTime);
        }
        else if (obstacles[i].kind == 28)
        {
            StaticEnemy* p = (StaticEnemy*)&obstacles[i];
            p->Update(&player, deltaTime);
        }
    }
     
    
    /* equal to movable class's update function */
    for (int i = 0; i < movables.size(); i++)
    {
        // reset to be movable before checking each frame
        movables[i].canMove = true;
        
        /* eventual movable checking */
        if (movables[i].GetCurrentDir() != 0)
        {
            for (int j = 0; j < obstacles.size(); j++)
                if (movables[i].DetectCollision(&obstacles[j]))
                    movables[i].Collision(&obstacles[j]);
            for (int j = 0; j < movables.size(); j++)
                if (movables[i].DetectCollision(&movables[j]) && j != i)
                    movables[i].Collision(&movables[j]);
            for (int j = 0; j < collectables.size(); j++)
                if (movables[i].DetectCollision(&collectables[j]))
                    movables[i].Collision(&collectables[j]);
        }
    }
    
    // update for the obstacle enemies in egg state
    for (int i = 0; i < eggs.size(); i++)
    {
        // reset to be movable before checking each frame
        eggs[i].canMove = true;
        eggs[i].Update(&player, *this, deltaTime);
        if (eggs[i].GetEggTime() < 0)
        {
            if (eggs[i].GetEnemyKind() == 26)
            {
                Element obstacleUnit = Element(eggs[i].centerX - 0.5f * LIB::LENGTH_UNIT, eggs[i].centerY -  0.5f * LIB::HEIGHT_UNIT, LIB::LENGTH_UNIT, LIB::HEIGHT_UNIT, &textureObstacleEnemy, LIB::ANIM_ENEMY1_NUM_HORIZONTAL, LIB::ANIM_ENEMY1_NUM_VERTICAL, 26);
                obstacles.push_back(obstacleUnit);
            }
            eggs.erase(eggs.begin() + i);
        }

        /* eventual movable checking */
        if (eggs[i].GetCurrentDir() != 0)
        {
            for (int j = 0; j < obstacles.size(); j++)
                if (eggs[i].DetectCollision(&obstacles[j]))
                    eggs[i].Collision(&obstacles[j]);
            for (int j = 0; j < eggs.size(); j++)
                if (eggs[i].DetectCollision(&eggs[j]) && j != i)
                    eggs[i].Collision(&eggs[j]);
            for (int j = 0; j < collectables.size(); j++)
                if (eggs[i].DetectCollision(&collectables[j]))
                    eggs[i].Collision(&collectables[j]);
        }
    }
    
    /* update for collectable class */
    for (int i = 0; i < collectables.size(); i++)
    {
        if (collectables[i].GetIsCollided())
        {
            if (collectables[i].kind == 31)
            {
                UpdateHeartLeft();
            }
            else if (collectables[i].kind == 32)
            {
                UpdatePlayerProjectileNum();
            }
            collectables.erase(collectables.begin() + i);
        }
        
    }
    
    /* make door trigger active if the key is got */
    for (int i = 0; i < triggers.size(); i++)
    {
        // keybox
        if (triggers[i].GetTrigger() && triggers[i].kind == 62)
        {
            CleanLevelEnemy();
            // erase closed door
            for (int j = 0; j < obstacles.size(); j++)
            {
                if(obstacles[j].kind == 61)
                    obstacles.erase(obstacles.begin() + j);
            }
            // show open door
            for (int j = 0; j < triggers.size(); j++)
            {
                if(triggers[j].kind == 61)
                {
                    triggers[j].SetIsTriggerActive(true);
                }
            }
        }
        // door
        if (triggers[i].GetTrigger() && triggers[i].kind == 61)
        {
            if (currentLevel < MAX_LEVEL)
            {
                currentLevel++;
                InitLevel(currentLevel);
            }
        }
    }
    
    /* text update, will be placed in a condition when they change */
    textLife.setString(to_string(player.GetLifePoint()));
    textWeapon.setString(to_string(playerProjectileNum));
}


void Level::Render(sf::RenderWindow &window)
{
    for (int i = 0; i < background.size(); i++)
    {
        background[i].Render(window);
    }
    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i].Render(window);
    }
    for (int i = 0; i < collectables.size(); i++)
    {
        collectables[i].Render(window);
    }
    for (int i = 0; i < movables.size(); i++)
    {
        movables[i].Render(window);
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Render(window);
    }
    
    for (int i = 0; i < eggs.size(); i++)
    {
        eggs[i].Render(window);
    }
     
    for (int i = 0; i < triggers.size(); i++)
    {
        if (triggers[i].GetIsTriggerActive())
            triggers[i].Render(window);
        if (triggers[i].kind == 62)
            triggers[i].Render(window);
    }
    
    
    if (playerProjectile.GetIsUsing())
        playerProjectile.Render(window);
    
    player.Render(window);
    
    uiLife.Render(window);
    uiWeapon.Render(window);
    
    window.draw(title);
    window.draw(textLife);
    window.draw(textWeapon);
}
