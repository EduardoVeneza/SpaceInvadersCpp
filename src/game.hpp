#pragma once
#include "Spaceship.hpp"

class Game {
    public:
    Game();
    ~Game();
    void update();
    void draw();
    void handleImput();
    void deleteInactiveLasers();


    private:
        Spaceship spaceship;
};