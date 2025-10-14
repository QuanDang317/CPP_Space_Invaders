#include "game_over.hpp"
#include <raylib.h>

void GameOver::Update() {
    // Nếu người chơi nhấn phím Enter, đặt cờ restartRequested = true để báo hiệu muốn chơi lại
    if (IsKeyPressed(KEY_ENTER)) {
        restartRequested = true;
    }
}

void GameOver::Draw() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char* text1 = "GAME OVER";
    const char* text2 = "Press [ENTER] to Restart";

    int fontSize1 = 80;
    int fontSize2 = 30;

    // Tính chiều dài của text để canh giữa màn hình
    int text1Width = MeasureText(text1, fontSize1);
    int text2Width = MeasureText(text2, fontSize2);

    // Tính vị trí x, y để canh giữa
    int text1X = (screenWidth - text1Width) / 2;
    int text1Y = screenHeight / 2 - fontSize1;

    int text2X = (screenWidth - text2Width) / 2;
    int text2Y = text1Y + fontSize1 + 20; // cách text trên 20 pixel

    DrawText(text1, text1X, text1Y, fontSize1, RED);
    DrawText(text2, text2X, text2Y, fontSize2, RAYWHITE);
}
