#include "alien.hpp"

Texture2D Alien::alienTexture[] = {};

Alien::Alien(int tipo, Vector2 alienPosition)
{
    this->tipo = tipo;
    this->alienPosition = alienPosition;
    if (alienTexture[tipo - 1].id == 0)
    {
    
    
    switch (this->tipo)
    {
    case 1:
        alienTexture[0] = LoadTexture("Graphics/alien_1.png");
        break;
    case 2:
        alienTexture[1] = LoadTexture("Graphics/alien_2.png");
        break;
    case 3:
        alienTexture[2] = LoadTexture("Graphics/alien_3.png");
        break;
    default:
        alienTexture[0] = LoadTexture("Graphics/alien_1.png");
        break;
    }
    }
}
void Alien::draw(){
    DrawTextureV(alienTexture[tipo - 1], alienPosition, WHITE);
}

void Alien::update(int direction)
{
    alienPosition.x += direction;
}

int Alien::getTipo() {
    return tipo;
}

void Alien::unloadAliens()
{  
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(alienTexture[i]);
    }
    
}

Rectangle Alien::getRectangle()
{
    return {alienPosition.x, alienPosition.y,
    float(alienTexture[tipo - 1].width),
    float(alienTexture[tipo - 1].height)
    };
}
