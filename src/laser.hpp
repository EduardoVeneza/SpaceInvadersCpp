#pragma once
#include <raylib.h>


class Laser
{
public:
    Laser(Vector2 laserPosition, int speed);
    void update();
    void draw();
    bool active;
    Rectangle getRectangle();

private:
    Vector2 laserPosition;
    int speed;
};