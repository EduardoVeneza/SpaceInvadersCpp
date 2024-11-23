#include "raylib.h"
#include "game.hpp"

int main()
{
  Color grey = {29, 29, 27, 255};
  int windowHeight = 700;
  int windowWidgth = 750;
  InitWindow(windowWidgth, windowHeight, "Space Invaders C++");
  SetTargetFPS(60);



  Game game;
  while (WindowShouldClose() == false)
  {

    
    BeginDrawing();
    ClearBackground(grey);

    game.handleImput();
    game.update();
    game.draw();



    EndDrawing();  
  }
  


  CloseWindow();
}