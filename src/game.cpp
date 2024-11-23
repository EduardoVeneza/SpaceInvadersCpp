#include "game.hpp"
#include <iostream>
Game::Game()
{

}

Game::~Game()
{

}

void Game::update()
{
    for(auto& laser: spaceship.lasers)
    {
        laser.update();
    }
    deleteInactiveLasers();
}

void Game::draw()
{
    spaceship.draw();

    for(auto& laser: spaceship.lasers)
    {
        laser.draw();
    }
}

void Game::handleImput()
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.moveLeft();
    } else if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.moveRight();
    } else if(IsKeyDown(KEY_SPACE))
    {
        spaceship.fireLaser();
    }
    
}

void Game::deleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it -> active)
        {
            it = spaceship.lasers.erase(it);
        } else {
            it++;
        }
        
    }
    
}
