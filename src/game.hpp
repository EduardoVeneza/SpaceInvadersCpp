#pragma once
#include "Spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryShip.hpp"


class Game {
    public:
    Game();
    ~Game();
    void update();
    void draw();
    void drawInterface(Font gameFont, Color color);
    void showMenu(Font menuFont, Color menuColor);
    void handleImput();
    void deleteInactiveLasers();
    bool isRunning;
    int lifes;
    int score;
    Music music;
    

    private:
        Spaceship spaceship;
        int ObstacleQTD = 4;
        mysteryShip mysteryship;
        std::vector<obstacle> create_obstacle();
        std::vector<Alien> create_aliens();
        void InitSounds();
        void addScore(int value);
        void moveAliens();
        void gameover();
        void moveAliensDown(int down);
        void alienShootLaser();
        void checkForCollision();
        void resetGame();
        void InitGame();
        int alienDirection;
        std::vector<obstacle> obstacles;
        std::vector<Alien> Aliens;
        std::vector<Laser> alienLasers;
        float alienShootTime = 0.35;
        float timeLastAlienFired;
        float mysteryShipSpawnInterval;
        float lastMysteryShipSpawn;
        Sound explosionSound;
        Sound laserShootSound;
};