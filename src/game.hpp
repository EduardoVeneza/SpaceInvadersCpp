#pragma once
#include "Spaceship.hpp"
#include "obstacle.hpp"


class Game {
    public:
    Game();
    ~Game();
    void update();
    void draw();
    void handleImput();
    void deleteInactiveLasers();


    private:
        std::vector<obstacle> create_obstacle();
        Spaceship spaceship;
        std::vector<obstacle> obstacles;
};