#include "game.hpp"
#include <iostream>
Game::Game(Font gameFont, Color gameColor)
{
    InitSounds();
    InitGame();
    this->gameFont = gameFont;
    this->gameColor = gameColor;
}

Game::~Game()
{
    Alien::unloadAliens();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
    UnloadSound(laserShootSound);
}

void Game::update()
{

    if (isRunning)
    {
        double currentTime = GetTime();
        if (currentTime - lastMysteryShipSpawn > mysteryShipSpawnInterval)
        {
            mysteryship.spawn();
            lastMysteryShipSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto &laser : spaceship.lasers)
        {
            laser.update();
        }
        deleteInactiveLasers();

        moveAliens();

        alienShootLaser();

        for (auto &laser : alienLasers)
        {
            laser.update();
        }
        mysteryship.update();
        checkForCollision();
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            resetGame();
        }
    }
}

void Game::draw()
{
    spaceship.draw();

    for (auto &laser : spaceship.lasers)
    {
        laser.draw();
    }

    for (auto &obstacle : obstacles)
    {
        obstacle.draw();
    }

    for (auto &alien : Aliens)
    {
        alien.draw();
    }

    for (auto &laser : alienLasers)
    {
        laser.draw();
    }
    mysteryship.draw();
}

void Game::handleImput()
{                               // Verifica se o jogo está rodando
    if (isRunning && !isInMenu) // Verifica se está no menu e se o jogo está rodando (Not Game Over)
    {
        // Verifica se as teclas LEFT, RIGHT, SPACE estão sendo pressionadas (a cada frame), e chama as funções respectivas
        if (IsKeyDown(KEY_LEFT))
        {
            spaceship.moveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.moveRight();
        }
        else if (IsKeyDown(KEY_SPACE))
        {
            spaceship.fireLaser(laserShootSound);
        }
        else if (IsKeyDown(KEY_R)) // Retorna ao menu, tornando IsInMenu Verdadeiro
        {
            isInMenu = !isInMenu;
        }
    }
    else
    { //Controles em Menu
        if (!isInOptions)
        {
            if (IsKeyDown(KEY_S)) // Inicia o jogo, tornando IsInMenu falso
            {
                isInMenu = !isInMenu;
            }
            else if (IsKeyDown(KEY_E)) // Fecha o jogo
            {
                exit(1);
            }
            else if (IsKeyDown(KEY_O)) // entra em options: Menu -> options
            {
                isInOptions = !isInOptions;
            }
        }
        else
        { //Controles no Options
            if (IsKeyDown(KEY_M)) // Retorna ao menu: Options -> menu
            {
                isInOptions = !isInOptions;
            } else if (IsKeyDown(KEY_ONE)) {
                gameColor = BLUE;
            } else if (IsKeyDown(KEY_TWO)){
                gameColor = RED;
            } else if (IsKeyDown(KEY_THREE)){
                gameColor = GREEN;
            } else if (IsKeyDown(KEY_FOUR)){
                gameColor = YELLOW;
            } else if (IsKeyDown(KEY_FIVE)){
                gameColor = PURPLE;
            } else if (IsKeyDown(KEY_Q)) {
                soundIsOn = !soundIsOn;
                double currentTime = GetTime();
                if (currentTime - lastSoundTime <= 1.5)
                {
                    if (soundIsOn)
                    {
                        SetMusicVolume(music, 0);
                    } else {
                        SetMusicVolume(music, 1);
                    }
                }
                lastSoundTime = GetTime();
                
            }
        }
    }
}

void Game::drawInterface()
{
    // Desenha os FPS
    // DrawFPS(GetScreenWidth()/2 - 50, 40);

    // Desenha a caixa aonde se passa o jogo
    DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, gameColor);

    // Desenha a linha que divide interface de jogo
    DrawLineEx({10, 730}, {790, 730}, 3, gameColor);

    // Verifica se o jogo ainda está rodando, se houver game over, indique ao jogador
    if (isRunning)
    {
        DrawTextEx(gameFont, "LEVEL 01 - Press R to return to menu", {250, 740}, 26, 2, gameColor);
    }
    else
    {
        DrawTextEx(gameFont, "GAME OVER (PRESS ENTER TO RESET)", {140, 740}, 34, 2, gameColor);
    }
    // Desenha as vidas, e subtrai uma sempre que a nave for atingida
    float x = 60.0f;
    for (int i = 0; i < lifes; i++)
    {
        DrawTextureV(spaceship.getSpaceshipTexture(), {x, 755}, WHITE);
        x += 50;
    }

    // Desenha o score, ultiliza "TextFormat()" para converter o INT em STRING
    DrawTextEx(gameFont, TextFormat("Score: %d", score), {600, 40}, 30, 3, gameColor);
}

void Game::showMenu()
{
    if (!isInOptions)
    { // Interface do menu fora de options
        DrawTextEx(gameFont, "SPACE-INVADERS", {220, 100}, 50, 3, gameColor);
        DrawTextEx(gameFont, "S - START", {220, 400}, 34, 3, gameColor);
        DrawTextEx(gameFont, "O - OPTIONS", {220, 450}, 34, 3, gameColor);
        DrawTextEx(gameFont, "E - EXIT", {220, 500}, 34, 3, gameColor);
    }
    else
    { // Interface do menu de options
        DrawTextEx(gameFont, "SPACE-INVADERS", {220, 100}, 50, 3, gameColor);
        DrawTextEx(gameFont, "(UN)MUTE MUSIC -> Q", {400, 400}, 34, 3, gameColor);
        DrawTextEx(gameFont, "THEMES: ", {100, 400}, 34, 3, gameColor);
        DrawTextEx(gameFont, "1 - BLUE", {125, 440}, 34, 3, gameColor);
        DrawTextEx(gameFont, "2 - RED", {125, 480}, 34, 3, gameColor);
        DrawTextEx(gameFont, "3 - GREEN", {125, 520}, 34, 3, gameColor);
        DrawTextEx(gameFont, "4 - YELLOW", {125, 560}, 34, 3, gameColor);
        DrawTextEx(gameFont, "5 - PURPLE", {125, 600}, 34, 3, gameColor);
        DrawTextEx(gameFont, "M - MENU", {100, 640}, 34, 3, gameColor);
    }
}

void Game::deleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->active)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            it++;
        }
    }
}

std::vector<obstacle> Game::create_obstacle()
{
    int obstacleWidth = obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (ObstacleQTD * obstacleWidth)) / (ObstacleQTD + 1);

    for (int i = 0; i < ObstacleQTD; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(obstacle({offsetX, float(GetScreenHeight() - 100) - 100}));
    }
    return obstacles;
}

std::vector<Alien> Game::create_aliens()
{

    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 11; coluna++)
        {
            int tipodoalien;
            float x = 75 + coluna * 55;
            float y = 110 + linha * 55;
            if (linha == 0)
            {
                tipodoalien = 3;
            }
            else if (linha > 0 && linha < 3)
            {
                tipodoalien = 2;
            }
            else
            {
                tipodoalien = 1;
            }

            Aliens.push_back(Alien(tipodoalien, {x, y}));
        }
    }
    return Aliens;
}

void Game::InitSounds()
{
    music = LoadMusicStream("Sound/music.ogg");
    explosionSound = LoadSound("Sound/explosion.ogg");
    laserShootSound = LoadSound("Sound/laser.ogg");
    PlayMusicStream(music);
}

void Game::addScore(int value)
{
    this->score += value;
}

void Game::moveAliens()
{
    for (auto &alien : Aliens)
    {
        if (alien.alienPosition.x + alien.alienTexture[alien.tipo - 1].width > GetScreenWidth() - 15)
        {
            moveAliensDown(5);
            alienDirection = -1;
        }
        if (alien.alienPosition.x < 15)
        {
            moveAliensDown(5);
            alienDirection = 1;
        }

        alien.update(alienDirection);
    }
}

void Game::gameover()
{
    isRunning = false;
}

void Game::moveAliensDown(int down)
{
    for (auto &alien : Aliens)
    {
        alien.alienPosition.y += down;
    }
}

void Game::alienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienShootTime && !Aliens.empty())
    {
        int randomIdexValue = GetRandomValue(0, Aliens.size() - 1);
        Alien &alienptr = Aliens[randomIdexValue];
        alienLasers.push_back(Laser({alienptr.alienPosition.x + alienptr.alienTexture[alienptr.tipo - 1].width / 2,
                                     alienptr.alienPosition.y + alienptr.alienTexture[alienptr.tipo - 1].height},
                                    6));
        timeLastAlienFired = GetTime();
    }
}

void Game::checkForCollision()
{
    // Checa colisão entre: Spaceship Laser e Alien
    for (auto &laser : spaceship.lasers)
    {
        auto it = Aliens.begin();

        while (it != Aliens.end())
        {
            if (CheckCollisionRecs(it->getRectangle(), laser.getRectangle()))
            {
                if (it->getTipo() == 1)
                {
                    std::cout << "Alien Tipo 1, pontos -> 100" << std::endl;
                    addScore(100);
                }
                else if (it->getTipo() == 2)
                {
                    std::cout << "Alien Tipo 2, pontos -> 200" << std::endl;
                    addScore(200);
                }
                else if (it->getTipo() == 3)
                {
                    std::cout << "Alien Tipo 3, pontos -> 300" << std::endl;
                    addScore(300);
                }
                it = Aliens.erase(it);
                PlaySound(explosionSound);

                laser.active = false;
            }
            else
            {
                it++;
            }
        }

        // Checa colisão entre: Spaceship Laser e Obstacle
        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->getRectangle(), laser.getRectangle()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    it++;
                }
            }
        }
        // Checa colisão entre: Spaceship Laser e MysteryShip
        if (CheckCollisionRecs(mysteryship.getRectangle(), laser.getRectangle()))
        {
            mysteryship.alive = false;
            PlaySound(explosionSound);
            addScore(500);
            laser.active = false;
        }
    }
    for (auto &alienlaser : alienLasers)
    {
        // Checa colisão entre: Alien Laser e Spaceship
        if (CheckCollisionRecs(alienlaser.getRectangle(), spaceship.getRectangle()))
        {
            alienlaser.active = false;
            lifes--;
            if (lifes == 0)
            {
                gameover();
            }
        }
        // Checa colisão entre: Alien Laser e obstacle
        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->getRectangle(), alienlaser.getRectangle()))
                {
                    it = obstacle.blocks.erase(it);
                    alienlaser.active = false;
                }
                else
                {
                    it++;
                }
            }
        }
    }
    // Checa colisão entre: Os próprios aliens, e obstacle
    for (auto &alien : Aliens)
    {
        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->getRectangle(), alien.getRectangle()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }
}

void Game::resetGame()
{
    spaceship.resetSpaceship();
    Aliens.clear();
    obstacles.clear();
    alienLasers.clear();
    InitGame();
}

void Game::InitGame()
{
    obstacles = create_obstacle();
    Aliens = create_aliens();
    alienDirection = 1;
    timeLastAlienFired = 0.0;
    lastMysteryShipSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lifes = 3;
    isRunning = true;
    isInMenu = true;
    isInOptions = false;
    score = 0;
}
