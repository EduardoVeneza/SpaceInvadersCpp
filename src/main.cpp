
#include "raylib.h"

int main()
{
  int windowHeight = 700;
  int windowWidgth = 750;

  InitWindow(windowWidgth, windowHeight, "Space Invaders C++");
  SetTargetFPS(60);

  while (WindowShouldClose() == false)
  {
    BeginDrawing();
    EndDrawing();  
  }
  


  CloseWindow();
}