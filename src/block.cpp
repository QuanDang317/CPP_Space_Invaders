#include "block.hpp"

Block::Block(Vector2 position) // truyen vi tri cho block qua position
{
    this -> position = position; // gan vi tri
}

void Block::Draw() {
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255}); // Vẽ hình chữ nhật đại diện cho Block với màu vàng
}

Rectangle Block::getRect() // Lấy hình chữ nhật bao quanh Block
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}
