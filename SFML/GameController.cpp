//
//  GameController.cpp
//  SFML
//
//  Created by ZEMIN on 14/10/2019.
//  Copyright © 2019 ZEMIN. All rights reserved.
//
#include "LIB.hpp"

GameController::GameController() : window(sf::VideoMode(LENGTH, HEIGHT), "C++ Game"),  inputController(), menu(LENGTH, HEIGHT),  level(1)
{
    window.setFramerateLimit(120);
    state = Menu;
}




void GameController::EndApplication()
{
    cout << "\n !!!Ending Application!!! \n";
}

// update the 'deltaTime' with the time it takes to update and render one frame
void GameController::UpdateTime()
{
    deltaTime = deltaTimeClock.restart().asSeconds();
    
    renderTime = renderClock.getElapsedTime().asSeconds();
    if (renderTime > 0.12f)
    {
        renderTime = renderClock.restart().asSeconds();
        Render();
    }
    
}

void GameController::UpdateSFMLEvents()
{
    while (window.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::KeyReleased:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                        
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                    {
                        switch (menu.GetPressedItem()) {
                            case 0:
                                state = InGame;
                                break;
                                
                            case 1:
                                cout << "option" << endl;
                                break;
                                
                            case 2:
                                window.close();
                                break;
                                
                            default:
                                break;
                        }
                    }
                        break;
                        
                }
            }
                break;
                
            default:
                break;
        }
        
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void GameController::Update()
{
    UpdateSFMLEvents();
    inputController.UpdateInput(level.player);
    
    if (state == InGame)
        level.Update(deltaTime);
    
    UpdateTime();
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        EndApplication();
        window.close();
    }
}

// execute nearest state's render functions
void GameController::Render()
{
    window.clear();
    
    if (state == Menu)
        menu.Render(window);
    
    else if (state == InGame)
        level.Render(window);
    
    window.display();
}

void GameController::Run()
{
    while (window.isOpen())
    {
        Update();
    }
}
