#include "game.hpp"
#include <iostream>
Game::Game()
{
    obstacles = create_obstacle();
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

    for (auto& obstacle : obstacles)
    {
        obstacle.draw();
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

std::vector<obstacle> Game::create_obstacle()
{
    int obstacleWidth = obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i+1) * gap + 1 * obstacleWidth;
        obstacles.push_back(obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}
