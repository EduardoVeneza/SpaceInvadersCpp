#pragma once
#include "Spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"


class Game {
    public:
    Game();
    ~Game();
    void update();
    void draw();
    void handleImput();
    void deleteInactiveLasers();


    private:
        int ObstacleQTD = 4;
        std::vector<obstacle> create_obstacle();
        std::vector<Alien> create_aliens();
        void moveAliens();
        void moveAliensDown(int down);
        void alienShootLaser();
        int alienDirection;
        Spaceship spaceship;
        std::vector<obstacle> obstacles;
        std::vector<Alien> Aliens;
        std::vector<Laser> alienLasers;
        float alienShootTime = 0.35;
        float timeLastAlienFired;
};