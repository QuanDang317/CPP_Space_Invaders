#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship{ // Tàu vũ trụ của người chơi
    public:
        Spaceship(); // Ham khởi tạo
        ~Spaceship(); // Ham hủy
        void Draw(); // Ham vẽ
        void MoveLeft(); // Ham di chuyển sang trái
        void MoveRight(); // Ham di chuyển sang phải
        void FireLaser(); // Ham bắn laser
        Rectangle getRect(); // Ham lấy hình chữ nhật bao quanh tàu
        void Reset(); // Ham đặt lại trạng thái tàu
        std::vector<Laser> lasers; // Danh sách các tia laser bắn ra từ tàu

    private:
        Texture2D image; // Hình ảnh tàu
        Vector2 position; // Vị trí tàu
        double lastFireTime; // Thời gian bắn laser cuối
        Sound laserSound; // Âm thanh bắn laser
};