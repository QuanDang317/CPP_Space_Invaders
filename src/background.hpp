#pragma once
#include <raylib.h>

const int STAR_COUNT = 250; // Số lượng ngôi sao trong nền

struct Star {
    float x; // Vị trí x của ngôi sao
    float y; // Vị trí y của ngôi sao
    float speed; // Tốc độ di chuyển của ngôi sao
};

class Background { // Quản lý nền sao chuyển động
public:
    Background(int screenWidth, int screenHeight); 
    void Update(); 
    void Draw(); 

private:
    Star stars[STAR_COUNT]; 
    int screenWidth; 
    int screenHeight;
    
};
