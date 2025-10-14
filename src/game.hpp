#pragma once

#include <vector> // Sử dụng vector để quản lý các đối tượng
#include "spaceship.hpp" // Bao gồm định nghĩa lớp Spaceship
#include "obstacle.hpp" // Bao gồm định nghĩa lớp Obstacle
#include "alien.hpp" // Bao gồm định nghĩa lớp Alien
#include "mysteryship.hpp" // Bao gồm định nghĩa lớp MysteryShip
#include "background.hpp" // Bao gồm định nghĩa lớp Background
#include <raylib.h>

class Game {
public:
    Game();
    ~Game();

    void Draw();
    void Update();
    void HandleInput(); // Xử lý đầu vào từ người chơi

    void Reset();  // Đưa Reset vào public để gọi ngoài được

    bool run;
    int lives;
    int score;
    int highscore;
    Music music;
    Background background;

    // Quản lý level và trạng thái chuyển level public nếu cần truy cập ngoài
    int currentLevel;
    bool isLevelTransition;
    float levelTransitionTimer;

private:
    float timeSinceLastDown = 0.0f;
    float baseDownInterval = 5.0f; // Thời gian mặc định (giây)
    void DeleteInactiveLasers(); // Xóa các tia laser không còn hoạt động
    std::vector<Obstacle> CreateObstacles();       // Tạo chướng ngại vật
    std::vector<Alien> CreateAliens();              // Tạo kẻ thù
    void MoveAliens();                              // Di chuyển kẻ thù
    void MoveDownAliens(int distance);              // Di chuyển kẻ thù xuống dưới
    void AlienShootLaser();                          // Kẻ thù bắn laser
    void CheckForCollisions();                       // Kiểm tra va chạm
    void GameOver();                          // Xử lý khi game kết thúc
    void InitGame();      // Khởi tạo trạng thái game   
    void checkForHighscore();   // Kiểm tra và cập nhật điểm cao
    void saveHighscoreToFile(int highscore); // Lưu điểm cao vào tệp
    int loadHighscoreFromFile(); // Tải điểm cao từ tệp
    bool isPaused;
    Spaceship spaceship;    // Tàu vũ trụ của người chơi
    std::vector<Obstacle> obstacles;  // Danh sách chướng ngại vật
    std::vector<Alien> aliens;  // Danh sách kẻ thù
    int aliensDirection;  // Hướng di chuyển của kẻ thù
    std::vector<Laser> alienLasers;  // Danh sách tia laser của kẻ thù
    constexpr static float alienLaserShootInterval = 0.35f;  // Thời gian giữa các lần bắn laser của kẻ thù
    float timeLastAlienFired;  // Thời gian kẻ thù bắn laser lần cuối
    MysteryShip mysteryship;
    float mysteryShipSpawnInterval;
    float timeLastSpawn;
    Sound explosionSound;

    const float levelTransitionDuration = 3.5f;
};
