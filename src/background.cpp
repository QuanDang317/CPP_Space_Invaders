#include "background.hpp" 

Background::Background(int screenWidth, int screenHeight) // Constructor
    : screenWidth(screenWidth), screenHeight(screenHeight) {
    for (int i = 0; i < STAR_COUNT; i++) {
        stars[i].x = GetRandomValue(0, screenWidth); // GetRandomValue là hàm trong Raylib để lấy giá trị ngẫu nhiên trong khoảng
        stars[i].y = GetRandomValue(0, screenHeight);
        stars[i].speed = GetRandomValue(20, 100) / 100.0f; 
    }
}

void Background::Update() {
    for (int i = 0; i < STAR_COUNT; i++) {
        stars[i].y += stars[i].speed;
        if (stars[i].y > screenHeight) {
            stars[i].y = 0;
            stars[i].x = GetRandomValue(0, screenWidth);
        }
    }
}

void Background::Draw() {
    for (int i = 0; i < STAR_COUNT; i++) {
        // Kích thước sao tỉ lệ theo tốc độ rơi
        float radius = stars[i].speed * 2.0f;

        // Màu trắng sáng trong suốt (alpha 200)
        Color innerColor = {255, 255, 255, 200};

        // Màu ngoài mờ hơn để tạo hiệu ứng "phát sáng"
        Color outerColor = {255, 255, 255, 60};

        Vector2 pos = { stars[i].x, stars[i].y };

        // Vẽ phần lõi sáng
        DrawCircleV(pos, radius, innerColor);

        // Vẽ phần ngoài mờ nhẹ để tạo glow
        DrawCircleV(pos, radius * 1.5f, outerColor);
    }
}

