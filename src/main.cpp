#include "raylib.h"
#include "game.hpp"

int main()
{
  Color grey = {29, 29, 27, 255};
  Color yellow = {243, 216, 63, 255};
  int offset = 50;
  int windowHeight = 700;
  int windowWidth = 750;
  InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invaders C++");
  SetTargetFPS(60);
  Font gameFont = LoadFontEx("fonts/monogram.ttf", 64, 0, 0);
  
  Game game;
  while (WindowShouldClose() == false)
  {

    game.handleImput();
    game.update();
    
    BeginDrawing();
    ClearBackground(grey);
    DrawRectangleRoundedLines({10,10,780,780}, 0.18f, 20, yellow);
    DrawLineEx({10, 730}, {790,730}, 3, yellow);

    if (game.isRunning)
    {
      DrawTextEx(gameFont, "LEVEL 01", {570, 740}, 34, 2, yellow);
    } else {
      DrawTextEx(gameFont, "GAME OVER (PRESS ENTER TO RESET)", {140, 740}, 34, 2, yellow);
    }

    float x = 60.0f;
    for (int i = 0; i < game.lifes; i++)
    {
      DrawTextureV(game.spaceship.getSpaceshipTexture(), {x, 755}, WHITE);
      x += 50;
    }
    
    


    game.draw();

    EndDrawing();  
  }
  


  CloseWindow();
}