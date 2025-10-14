#include "game.hpp"
#include <iostream>
#include <fstream>

// Constructor
Game::Game()
    : background(750 + 50, 700 + 2 * 50), currentLevel(1), isLevelTransition(false), levelTransitionTimer(0.0f) { 
    music = LoadMusicStream("Sounds/music.ogg"); // Nhạc nền
    explosionSound = LoadSound("Sounds/explosion.wav"); // Âm thanh nổ
    PlayMusicStream(music); // Bắt đầu phát nhạc nền
    InitGame(); // Khởi tạo trạng thái game
}

// Destructor
Game::~Game() {
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

// Khởi tạo lại game, gọi khi bắt đầu hoặc reset
void Game::InitGame() {
    obstacles = CreateObstacles(); // Tạo chướng ngại vật
    aliens = CreateAliens(); // Tạo kẻ thù
    aliensDirection = 1; 
    timeLastAlienFired = 0.0f; // Thời gian kẻ thù bắn laser lần cuối
    timeLastSpawn = 0.0f; 
    lives = 5; 
    score = 0;
    highscore = loadHighscoreFromFile(); // Tải điểm cao từ file
    run = true;

    mysteryShipSpawnInterval = GetRandomValue(10, 20); // Khoảng thời gian ngẫu nhiên để xuất hiện MysteryShip

    // currentLevel = 1;   // Bắt đầu từ level 1
    isLevelTransition = false;  
    levelTransitionTimer = 0.0f; 

    spaceship.Reset();
}

// Reset game trạng thái khi muốn chơi lại
void Game::Reset() {
    InitGame();
}

// Vẽ toàn bộ đối tượng game lên màn hình
void Game::Draw() {
    if (isLevelTransition) {  
       // Dòng chữ "LEVEL X COMPLETE!"
        std::string completeText = "LEVEL " + std::to_string(currentLevel - 1) + " COMPLETE!";
        std::string proceedText = "Proceeding to Level " + std::to_string(currentLevel);

        const char* lines[] = {"All aliens destroyed",proceedText.c_str()};

        int fontSize = 40;

        Vector2 completeTextSize = MeasureTextEx(GetFontDefault(), completeText.c_str(), fontSize, 2);
        DrawText(completeText.c_str(), (GetScreenWidth() - (int)completeTextSize.x) / 2, GetScreenHeight() / 3, fontSize, GREEN);

        int lineSpacing = 50;
        for (int i = 0; i < 2; i++) {
            Vector2 lineSize = MeasureTextEx(GetFontDefault(), lines[i], fontSize - 10, 2);
            DrawText(lines[i], (GetScreenWidth() - (int)lineSize.x) / 2, GetScreenHeight() / 3 + (i + 1) * lineSpacing, fontSize - 10, RAYWHITE);
    }

        // Vẽ alien đang di chuyển ngang khi chuyển màn
        for (auto& alien : aliens) {
            alien.Draw();
        }
    }
    else {
        spaceship.Draw();

        for (auto& laser : spaceship.lasers)
            laser.Draw();

        for (auto& obstacle : obstacles)
            obstacle.Draw();

        for (auto& alien : aliens)
            alien.Draw();

        for (auto& laser : alienLasers) 
            laser.Draw();

        mysteryship.Draw();
        //  Thêm đoạn này để hiển thị khi game đang tạm dừng
        if (isPaused) {
            const char* pauseText = "PAUSED - Press [P] to Resume";
            int fontSize = 30;
            Vector2 textSize = MeasureTextEx(GetFontDefault(), pauseText, fontSize, 2);
            DrawText(pauseText, (GetScreenWidth() - (int)textSize.x) / 2, GetScreenHeight() / 2, fontSize, YELLOW);
        }
    }
}
void Game::GameOver() {
    run = false;
    currentLevel = 1; // reset lại level khi thua
}
// Cập nhật trạng thái game mỗi frame
void Game::Update() {
    if (!run || isPaused) return; // Dừng cập nhật nếu game over hoặc đang pause

    UpdateMusicStream(music);

    if (isLevelTransition) {
        levelTransitionTimer += GetFrameTime(); 

        // Alien di chuyển ngang khi chuyển màn
        for (auto& alien : aliens) {
            alien.position.x += aliensDirection * 30 * GetFrameTime();
        }

        if (levelTransitionTimer >= levelTransitionDuration) {
            // Kết thúc chuyển màn
            isLevelTransition = false;
            levelTransitionTimer = 0.0f;

            // Tăng level và tạo lại alien
            aliens = CreateAliens();
            aliensDirection = 1;
        }
        return;
    }

    background.Update();

    float currentTime = GetTime();
    if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
        mysteryship.Spawn();
        timeLastSpawn = currentTime;
        mysteryShipSpawnInterval = GetRandomValue(10, 20);
    }

    for (auto& laser : spaceship.lasers)
        laser.Update();

    MoveAliens();
    AlienShootLaser();

    for (auto& laser : alienLasers)
        laser.Update();

    DeleteInactiveLasers();
    mysteryship.Update();
    CheckForCollisions();
     
    timeSinceLastDown += GetFrameTime(); // Cập nhật thời gian đã trôi qua kể từ lần di chuyển xuống cuối
    float downInterval = (baseDownInterval / currentLevel) * 1.15f; // Giảm thời gian di chuyển xuống khi level tăng
    if (timeSinceLastDown >= downInterval) {
        MoveDownAliens(10);
        timeSinceLastDown -= downInterval;
    }

     // Khi tất cả alien bị tiêu diệt, bắt đầu chuyển màn
    if (aliens.empty()) {
        // cung có thể tăng mạng ở đây 
        lives++;

        currentLevel++;          // Tăng level **ở đây**
        isLevelTransition = true; // Bật cờ chuyển màn
        levelTransitionTimer = 0.0f;
    }
}

// Xử lý input người chơi
void Game::HandleInput() {
    if (!run) return;

    if (IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;  // Toggle trạng thái pause
    }

    if (isPaused) return;  // Dừng xử lý input khác khi đang pause

    if (IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    }

    if (IsKeyDown(KEY_SPACE)) {
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end(); ) {
        if (!it->active)
            it = spaceship.lasers.erase(it); // Xóa tia laser không còn hoạt động
        else
            ++it; // Chuyển sang tia laser tiếp theo
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end(); ) {
        if (!it->active)
            it = alienLasers.erase(it); 
        else
            ++it;
    }
}

// Tạo các chướng ngại vật (obstacle)
std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5.0f;

    std::vector<Obstacle> newObstacles;
    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        newObstacles.emplace_back(Vector2{offsetX, float(GetScreenHeight() - 200)});
    }
    return newObstacles;
}

// Tạo alien ban đầu
std::vector<Alien> Game::CreateAliens() {
    std::vector<Alien> newAliens;
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {
            int alienType;
            if (row == 0) alienType = 3;
            else if (row == 1 || row == 2) alienType = 2;
            else alienType = 1;

            float x = 75 + column * 55;
            float y = 110 + row * 55;
            newAliens.emplace_back(alienType, Vector2{ x, y });
        }
    }
    return newAliens;
}

// Di chuyển alien theo chiều ngang, và xuống khi gặp biên
void Game::MoveAliens() {
    bool switchDirection = false; // kiểm tra có cần đổi hướng không
    for (auto& alien : aliens) {
        if (aliensDirection == 1 && alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            // Nếu alien chạm biên phải, đổi hướng (25 pixels trước mép phải màn hình.)
            switchDirection = true;
            break;
        }
        else if (aliensDirection == -1 && alien.position.x < 25) {
            // Nếu alien chạm biên trái, đổi hướng
            switchDirection = true;
            break;
        }
    }

    if (switchDirection) {
        aliensDirection = -aliensDirection; 
        MoveDownAliens(10);
    }

    for (auto& alien : aliens) {
        alien.position.x += aliensDirection * 20 * GetFrameTime(); // Di chuyển alien 20 pixels mỗi giây
    }
}

// Alien di chuyển xuống một khoảng cách nhất định
void Game::MoveDownAliens(int distance) {
    for (auto& alien : aliens) {
        alien.position.y += distance; 
    }
}

// Alien bắn laser
void Game::AlienShootLaser() {
    float currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.emplace_back(
            Vector2{alien.position.x + alien.alienImages[alien.type - 1].width / 2.0f,
                    alien.position.y + alien.alienImages[alien.type - 1].height},
            6
        );
        timeLastAlienFired = currentTime;
    }
}

// Kiểm tra va chạm trong game
void Game::CheckForCollisions() {
    // Spaceship lasers với Alien và obstacle và MysteryShip
    for (auto& laser : spaceship.lasers) {
        for (auto it = aliens.begin(); it != aliens.end();) {
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                PlaySound(explosionSound);

                if (it->type == 1) score += 100;
                else if (it->type == 2) score += 200;
                else if (it->type == 3) score += 300;

                checkForHighscore();

                it = aliens.erase(it);
                laser.active = false;
            }
            else {
                ++it;
            }
        }

        for (auto& obstacle : obstacles) {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            checkForHighscore();
            PlaySound(explosionSound);
        }
    }

    // Alien lasers với spaceship và obstacle
    for (auto& laser : alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--;
            if (lives <= 0) {
                GameOver();
            }
        }

        for (auto& obstacle : obstacles) {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else {
                    ++it;
                }
            }
        }
    }

    // Alien va chạm obstacle hoặc spaceship
    for (auto& alien : aliens) {
        for (auto& obstacle : obstacles) {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}


// Kiểm tra và cập nhật điểm cao
void Game::checkForHighscore() {
    if(score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

// Lưu điểm cao vào file
void Game::saveHighscoreToFile(int highscore) {  // Lưu điểm cao vào file
    std::ofstream file("highscore.dat", std::ios::binary); // Mở file ở chế độ nhị phân
    if(file.is_open()) { 
        file.write(reinterpret_cast<const char*>(&highscore), sizeof(highscore)); // Ghi điểm cao vào file
        file.close();
    }
}

// Đọc điểm cao từ file
int Game::loadHighscoreFromFile() { // Đọc điểm cao từ file
    int hs = 0;
    std::ifstream file("highscore.dat", std::ios::binary); // Mở file ở chế độ nhị phân
    if(file.is_open()) {
        file.read(reinterpret_cast<char*>(&hs), sizeof(hs)); // Đọc điểm cao từ file
        file.close();
    }
    return hs;
}
