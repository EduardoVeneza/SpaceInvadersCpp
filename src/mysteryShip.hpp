#pragma once
#include <raylib.h>

class mysteryShip
{
public:
    mysteryShip();
    ~mysteryShip();
    void update();
    void draw();
    void spawn();
    bool alive;
    Rectangle getRectangle();
private:
    Texture2D mysteryShipTexture;
    Vector2 mysteryShipPosition;
    int speed;
};