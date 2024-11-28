#include "game.hpp"
#include <iostream>
Game::Game()
{
    obstacles = create_obstacle();
    Aliens = create_aliens();
    alienDirection = 1;
    timeLastAlienFired = 0.0;
}

Game::~Game()
{
    Alien::unloadAliens();
}

void Game::update()
{
    for(auto& laser: spaceship.lasers)
    {
        laser.update();
    }
    deleteInactiveLasers();

    moveAliens();

    alienShootLaser();

    for (auto& laser : alienLasers)
    {
        laser.update();
    }
    

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

    for (auto& alien: Aliens)
    {
        alien.draw();
    }
    
    for (auto& laser: alienLasers)
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

    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it -> active)
        {
            it = alienLasers.erase(it);
        } else {
            it++;
        }
        
    }
    
}

std::vector<obstacle> Game::create_obstacle()
{
    int obstacleWidth = obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (ObstacleQTD * obstacleWidth))/(ObstacleQTD+1);

    for (int i = 0; i < ObstacleQTD; i++)
    {
        float offsetX = (i+1) * gap + i * obstacleWidth;
        obstacles.push_back(obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}

std::vector<Alien> Game::create_aliens()
{
    
    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 11; coluna++)
        {
            int tipodoalien;
            float x = 75 + coluna * 55;
            float y = 110 + linha * 55;
            if (linha == 0)
            {
                tipodoalien = 3;
            } else if(linha > 0 && linha < 3){
                tipodoalien = 2;
            } else {
                tipodoalien = 1;
            }
            
            Aliens.push_back(Alien(tipodoalien, {x,y}));
        }
        
    }
    return Aliens;
}

void Game::moveAliens()
{
    for (auto& alien: Aliens)
    {
        if (alien.alienPosition.x + alien.alienTexture[alien.tipo - 1].width > GetScreenWidth())
        {
            moveAliensDown(5);
            alienDirection = -1;
        }
        if (alien.alienPosition.x < 0)
        {
            moveAliensDown(5);
            alienDirection = 1;
        }
        
        alien.update(alienDirection);
    }
    
}

void Game::moveAliensDown(int down)
{
    for (auto& alien : Aliens)
    {
        alien.alienPosition.y += down;
    }
    
}

void Game::alienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienShootTime && !Aliens.empty()){
    int randomIdexValue = GetRandomValue(0, Aliens.size() - 1);
    Alien& alienptr = Aliens[randomIdexValue];
    alienLasers.push_back(Laser({alienptr.alienPosition.x + alienptr.alienTexture[alienptr.tipo - 1].width/2, 
                                alienptr.alienPosition.y + alienptr.alienTexture[alienptr.tipo - 1].height}, 6));
    timeLastAlienFired = GetTime();
}
}
