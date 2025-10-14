#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

void MysteryShip::Spawn() { // Hàm xuất hiện tàu bí ẩn
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if(side == 0) {
        position.x = 25;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;
}

Rectangle MysteryShip::getRect() // Hàm lấy hình chữ nhật bao quanh tàu
{
    if(alive){
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}

void MysteryShip::Update() { // Cập nhật vị trí tàu bí ẩn nếu nó đang xuất hiện
    if(alive) {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width -25 || position.x < 25) {
            alive = false;
        }
    }
}

void MysteryShip::Draw() { // Vẽ tàu bí ẩn nếu nó đang xuất hiện
    if(alive) {
        DrawTextureV(image, position, WHITE);
    }
}