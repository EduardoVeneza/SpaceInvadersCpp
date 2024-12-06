#include "raylib.h"
#include "game.hpp"

int main()
{
  Color grey = {29, 29, 27, 255};
  // Color yellow = {243, 216, 63, 255};
  int offset = 50;
  int windowHeight = 700;
  int windowWidth = 750;
  InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invaders C++");
  InitAudioDevice();
  SetTargetFPS(60);
  Font gameFont = LoadFontEx("fonts/monogram.ttf", 64, 0, 0);

  Game game(gameFont, YELLOW);
  while (WindowShouldClose() == false)
  {
    UpdateMusicStream(game.music);

    BeginDrawing();

    ClearBackground(grey);
    game.handleImput();

    if (game.isInMenu)
    {
      game.showMenu();
    }
    else
    {
      game.update();
      game.drawInterface();
      game.draw();
    }

    EndDrawing();
  }

  CloseWindow();
}