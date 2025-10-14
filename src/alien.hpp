#pragma once // chống include trùng file.
#include <raylib.h> 
//Vì .cpp chỉ chứa phần định nghĩa chi tiết
// Header .hpp chính là nơi định nghĩa "bản thiết kế" của class.
class Alien {
    public:
        Alien(int type, Vector2 position); // Constructor: tạo một Alien với loại và vị trí cụ thể
        void Update(int direction); // Cập nhật vị trí Alien theo hướng di chuyển
        void Draw(); // Vẽ Alien
        int GetType(); // Lấy loại Alien
        static void UnloadImages(); // Giải phóng tài nguyên hình ảnh
        Rectangle getRect(); // Lấy hình chữ nhật bao quanh Alien
        static Texture2D alienImages[3];  // Mảng tĩnh chứa hình ảnh của các loại Alien
        int type; // Loại Alien (1, 2, hoặc 3)
        Vector2 position; // Vị trí của Alien
    private:
};