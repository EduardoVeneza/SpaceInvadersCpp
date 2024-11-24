#pragma once
#include "block.hpp"
#include <vector>

class obstacle {
    public:
        obstacle(Vector2 obsPosition);
        // ~obstacle();
        void draw();
        Vector2 obsPosition;
        std::vector<block> blocks;
        static std::vector<std::vector<int>> grid;
    private:


};
