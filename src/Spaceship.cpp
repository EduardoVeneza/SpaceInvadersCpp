#include "Spaceship.hpp"


Spaceship::Spaceship(){
    
    SpaceshipTexture = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - SpaceshipTexture.width)/2;
    position.y = GetScreenHeight() - SpaceshipTexture.height - 100;

    lastShoot = 0.0;
}

Spaceship::~Spaceship(){
    UnloadTexture(SpaceshipTexture);
}

void Spaceship::draw(){
    DrawTextureV(SpaceshipTexture, position, WHITE);
}

void Spaceship::moveLeft(){

    position.x -= 3;
    if (position.x < 0 + 14)
    {
        position.x = 0 + 14;
    }
    
}

void Spaceship::moveRight(){
    position.x += 3;
    if (position.x > GetScreenWidth() - SpaceshipTexture.width - 14)
    {
        position.x = GetScreenWidth() - SpaceshipTexture.width - 14;
    }
}

void Spaceship::fireLaser(Sound laserShootSound)
{
    if (GetTime() - lastShoot >= 0.35)
    {
        lasers.push_back(Laser({position.x + SpaceshipTexture.width/2 - 2, position.y} ,-10));
        PlaySound(laserShootSound);    
        lastShoot = GetTime();
    }
    
}

void Spaceship::resetSpaceship()
{
    position.x = (GetScreenWidth() - SpaceshipTexture.width)/2.0f;
    position.y = GetScreenHeight() - SpaceshipTexture.height - 100;
}

Rectangle Spaceship::getRectangle()
{
    return {position.x, position.y, float(SpaceshipTexture.width), float(SpaceshipTexture.height)};
}

Texture2D Spaceship::getSpaceshipTexture()
{
    return SpaceshipTexture;
}
