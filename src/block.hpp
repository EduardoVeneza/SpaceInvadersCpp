#pragma once
#include <raylib.h>

class block
{
    public:
        block(Vector2 blockPosition);
        // ~block();
        void draw();
    private:
        Vector2 blockPosition;
};



