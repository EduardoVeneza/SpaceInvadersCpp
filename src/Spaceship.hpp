#pragma once
#include <raylib.h>

class Spaceship{
public:
    Spaceship();
    ~Spaceship();
    void draw(); 
    void moveRight();
    void moveLeft();
    void fireLaser();

private:
Texture2D SpaceshipTexture;
Vector2 position;

};