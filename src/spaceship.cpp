#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png"); // Tải hình ảnh tàu vũ trụ
    position.x = (GetScreenWidth() - image.width)/2; // Đặt vị trí
    position.y = GetScreenHeight() - image.height - 100; // 100 là khoảng cách từ đáy cửa sổ
    lastFireTime = 0.0;
    laserSound = LoadSound("Sounds/laser.ogg"); // Tải âm thanh bắn laser
}

Spaceship::~Spaceship() {
    UnloadTexture(image);   // Giải phóng hình ảnh tàu
    UnloadSound(laserSound); // Giải phóng âm thanh bắn laser
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
    position.x -= 7; // Tốc độ di chuyển
    if(position.x < 25) { 
        position.x = 25;
    }
}

void Spaceship::MoveRight() {
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

void Spaceship::FireLaser()
{
    if(GetTime() - lastFireTime >= 0.35) { // Giới hạn tốc độ bắn laser
        lasers.push_back(Laser({position.x + image.width/2 - 2,position.y},-6)); // Tạo tia laser mới và thêm vào danh sách
        lastFireTime = GetTime(); // Cập nhật thời gian bắn laser cuối
        PlaySound(laserSound); // Phát âm thanh bắn laser
    }
}

Rectangle Spaceship::getRect() // Hàm lấy hình chữ nhật bao quanh tàu
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset() // Hàm đặt lại trạng thái tàu
{
    position.x = (GetScreenWidth() - image.width)/ 2.0f; 
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}
