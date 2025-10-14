#include "alien.hpp" 

Texture2D Alien::alienImages[3] = {};  // Khởi tạo mảng tĩnh chứa hình ảnh của các loại Alien
// LoadTexture là hàm trong Raylib dùng để tải một ảnh từ file

Alien::Alien(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    if(alienImages[type -1].id == 0){

    switch (type) {
        case 1:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3: 
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            break;
        default:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
    }
}
}

void Alien::Draw() { // Vẽ Alien tại vị trí hiện tại
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

int Alien::GetType() { // Trả về loại Alien
    return type;
}

void Alien::UnloadImages() // Giải phóng tài nguyên hình ảnh
{
    for(int i = 0; i < 4; i++) {
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::getRect() // Lấy hình chữ nhật bao quanh Alien
{
    return {position.x, position.y,
    float(alienImages[type - 1].width),
    float(alienImages[type - 1].height)
    };
}

void Alien::Update(int direction) { // Cập nhật vị trí Alien theo hướng di chuyển
    position.x += direction;
}
