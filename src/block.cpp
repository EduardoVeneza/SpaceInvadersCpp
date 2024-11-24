#include "block.hpp"

block::block(Vector2 blockPosition)
{
    this->blockPosition = blockPosition;
}

void block::draw()
{  
    DrawRectangle(blockPosition.x, blockPosition.y, 3, 3, {243, 216, 63, 255});
}