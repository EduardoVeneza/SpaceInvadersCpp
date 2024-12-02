#include "mysteryShip.hpp"

mysteryShip::mysteryShip()
{
    mysteryShipTexture = LoadTexture("Graphics/mystery.png");
    alive = false;
}

mysteryShip::~mysteryShip()
{
    UnloadTexture(mysteryShipTexture);
}

void mysteryShip::update()
{
    if (alive)
    {
        mysteryShipPosition.x += speed;
    }
    if (mysteryShipPosition.x < 25|| mysteryShipPosition.x > GetScreenWidth() - mysteryShipTexture.width - 25)
    {
        alive = false;
    }
    
}

void mysteryShip::draw()
{
    if(alive){
    DrawTextureV(mysteryShipTexture, mysteryShipPosition, WHITE);
    }
}

void mysteryShip::spawn()
{
    mysteryShipPosition.y = 90;
    int side = GetRandomValue(0, 1);

    if (side == 0)
    {
        mysteryShipPosition.x = 25;
        speed = 3;
    } else {
        mysteryShipPosition.x = GetScreenWidth() - mysteryShipTexture.width - 25;
        speed = -3;
    }
    alive = true;
    
}

Rectangle mysteryShip::getRectangle()
{
    if (alive)
    {
        return {mysteryShipPosition.x, mysteryShipPosition.y, 
        float(mysteryShipTexture.width),
        float(mysteryShipTexture.height)
        };
    } else {
        return {mysteryShipPosition.x, mysteryShipPosition.y,
        0,
        0
        };
    }
    
}
