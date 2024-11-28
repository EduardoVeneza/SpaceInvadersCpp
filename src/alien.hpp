#pragma once
#include <raylib.h>

class Alien {
    public:
        Alien(int tipo, Vector2 alienPosition);
        void draw();
        void update(int direction);
        int getTipo();
        static void unloadAliens();
        static Texture2D alienTexture[3];
        Vector2 alienPosition;
        int tipo;
    private:
};