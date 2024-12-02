#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 laserPosition, int speed)
{
    this->laserPosition = laserPosition;
    this->speed = speed;
    active = true;
}

void Laser::draw()
{
    if (active)
        DrawRectangle(laserPosition.x, laserPosition.y, 4, 15, {243, 216, 63, 255});
}

Rectangle Laser::getRectangle()
{
   return {laserPosition.x, laserPosition.y, 4, 15};
}

void Laser::update(){
    laserPosition.y += speed;
    if (active)
    {
        if (laserPosition.y > GetScreenHeight() - 100|| laserPosition.y < 25)
        {
            active = false;
        }
        
    }
}
