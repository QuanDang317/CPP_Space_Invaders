#pragma once
#include <raylib.h>

class MysteryShip { // Tàu bí ẩn
    public:
        MysteryShip();
        ~MysteryShip();
        void Update();
        void Draw();
        void Spawn();
        Rectangle getRect(); // Hàm lấy hình chữ nhật bao quanh tàu
        bool alive; // Cờ để kiểm tra xem tàu có đang xuất hiện hay không
    private:
        Vector2 position;
        Texture2D image;
        int speed;
};