#include "Spaceship.hpp"


Spaceship::Spaceship(){
    
    SpaceshipTexture = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - SpaceshipTexture.width)/2;
    position.y = GetScreenHeight() - SpaceshipTexture.height;

    lastShoot = 0.0;
}

Spaceship::~Spaceship(){
    UnloadTexture(SpaceshipTexture);
}

void Spaceship::draw(){
    DrawTextureV(SpaceshipTexture, position, WHITE);
}

void Spaceship::moveLeft(){

    position.x -= 7;
    if (position.x < 0)
    {
        position.x = 0;
    }
    
}

void Spaceship::moveRight(){
    position.x += 7;
    if (position.x > GetScreenWidth() - SpaceshipTexture.width)
    {
        position.x = GetScreenWidth() - SpaceshipTexture.width;
    }
}

void Spaceship::fireLaser()
{
    if (GetTime() - lastShoot >= 0.35)
    {
        lasers.push_back(Laser({position.x + SpaceshipTexture.width/2 - 2, position.y} ,-6));    
        lastShoot = GetTime();
    }
    
}