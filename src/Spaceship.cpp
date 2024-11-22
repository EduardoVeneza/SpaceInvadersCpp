#include "Spaceship.hpp"

Spaceship::Spaceship(){
    SpaceshipTexture = LoadTexture("Graphics/spaceship.png");
    position.x = 100;
    position.y = 100;
}

Spaceship::~Spaceship(){
    UnloadTexture(SpaceshipTexture);
}

void Spaceship::draw(){
    DrawTextureV(SpaceshipTexture, position, WHITE);
}

// void Spaceship::moveLeft(){
    
// }

// void Spaceship::moveRight(){
    
// }

// void Spaceship::fireLaser(){
    
// }