#pragma once
#include <vector>
#include "block.hpp"

class Obstacle { // Lớp chướng ngại vật
    public:
        Obstacle(Vector2 position); // Constructor
        void Draw();
        Vector2 position;      // Vị trí của chướng ngại vật
        std::vector<Block> blocks; // Danh sách các khối tạo thành chướng ngại vật
        static std::vector<std::vector<int>> grid; // Lưới định nghĩa hình dạng chướng ngại vật
    private:
};