#pragma once
#include <raylib.h>
// vector2 la mot kieu du lieu struct co 2tp
class Block {
    public:
        Block(Vector2 position); // Constructor
        void Draw(); 
        Rectangle getRect(); 
    private:
        Vector2 position; 
};