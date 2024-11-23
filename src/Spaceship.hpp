#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship{
public:
    Spaceship();
    ~Spaceship();
    void draw(); 
    void moveRight();
    void moveLeft();
    void fireLaser();
    std::vector<Laser> lasers;

private:
    Texture2D SpaceshipTexture;
    Vector2 position;
    double lastShoot;


};