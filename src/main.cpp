#include "raylib.h"
#include "Spaceship.hpp"

int main()
{
  Color grey = {29, 29, 27, 255};
  int windowHeight = 700;
  int windowWidgth = 750;
  InitWindow(windowWidgth, windowHeight, "Space Invaders C++");
  SetTargetFPS(60);



  Spaceship Spaceship;
  while (WindowShouldClose() == false)
  {
    BeginDrawing();
    ClearBackground(grey);

    Spaceship.draw();



    EndDrawing();  
  }
  


  CloseWindow();
}