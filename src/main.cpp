#include <raylib.h>
#include <string>
#include "game.hpp"
#include "GameOpeningScreen.hpp"
#include "game_over.hpp"

// Hàm định dạng số với số lượng số 0 dẫn đầu
std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    if (leadingZeros > 0)
        return std::string(leadingZeros, '0') + numberText;
    return numberText;
}

int main()
{
    Color grey = {29, 29, 27, 255}; // Màu xám đậm cho nền
    Color yellow = {243, 216, 63, 255}; // Màu vàng cho văn bản
    Color blue = {30, 144, 255, 255}; // Màu xanh cho viền
    Color lightBlue = {173, 216, 230, 255}; // Màu xanh nhạt cho viền neon
    int offset = 50; 
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    // --- Tải nhiều ảnh nền khác nhau cho từng level ---
    Texture2D backgrounds[4];
    backgrounds[0] = LoadTexture("Graphics/Back_ground_1.png");
    backgrounds[1] = LoadTexture("Graphics/Back_ground_2.png");
    backgrounds[2] = LoadTexture("Graphics/Back_ground_3.png");
    backgrounds[3] = LoadTexture("Graphics/Back_ground_4.png");
    SetTargetFPS(60);

    Game game;
    GameOpeningScreen openingScreen;
    GameOver gameOver;

    while (!WindowShouldClose()) {
        // --- Chọn ảnh nền theo level ---
        int bgIndex = (game.currentLevel - 1) % 4;
        Texture2D currentBackground = backgrounds[bgIndex];

        Rectangle sourceRec = { 0.0f, 0.0f, (float)currentBackground.width, (float)currentBackground.height };
        Rectangle destRec = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
        Vector2 origin = { 0.0f, 0.0f };

        float deltaTime = GetFrameTime();
        UpdateMusicStream(game.music);

        if (openingScreen.IsActive()) {
            game.background.Update();
            openingScreen.Update(deltaTime);

            BeginDrawing();
            ClearBackground(grey);
            DrawTexturePro(currentBackground, sourceRec, destRec, origin, 0.0f, WHITE);
            game.background.Draw();
            openingScreen.Draw();
            EndDrawing();
        }
        else if (!game.run) {
            game.background.Update();
            gameOver.Update();

            BeginDrawing();
            ClearBackground(grey);
            DrawTexturePro(currentBackground, sourceRec, destRec, origin, 0.0f, WHITE);
            game.background.Draw();
            gameOver.Draw();
            EndDrawing();

            if (gameOver.IsRestartRequested()) {
                game.Reset();
                gameOver.Reset();
            }
        }
        else {
            game.HandleInput();
            game.Update();

            BeginDrawing();
            ClearBackground(grey);
            DrawTexturePro(currentBackground, sourceRec, destRec, origin, 0.0f, WHITE);
            game.background.Draw();

            if (game.isLevelTransition) {
                game.Draw();
                EndDrawing();
                continue;
            }

            // --- Giao diện UI ---
            DrawRectangleRoundedLinesEx((Rectangle){8, 8, 784, 784}, 0.18f, 20, 2, lightBlue);
            DrawRectangleRoundedLinesEx((Rectangle){10, 10, 780, 780}, 0.18f, 20, 3, blue);
            DrawRectangleRoundedLinesEx((Rectangle){12, 12, 776, 776}, 0.18f, 20, 1, yellow);
            DrawLineEx({25, 730}, {775, 730}, 3, yellow);

            std::string levelText = std::string("LEVEL ") + 
                std::string(game.currentLevel < 10 ? "0" : "") + std::to_string(game.currentLevel);
            DrawTextEx(font, levelText.c_str(), {570, 740}, 34, 2, yellow);

            float x = 50.0f;
            for (int i = 0; i < game.lives; i++) {
                DrawTextureV(spaceshipImage, {x, 745}, WHITE);
                x += 50;
            }

            DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
            std::string scoreText = FormatWithLeadingZeros(game.score, 5);
            DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

            DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
            std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
            DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);

            // --- Vẽ các đối tượng trong game ---
            game.Draw();

            EndDrawing();
        }
    }

    UnloadFont(font);
    UnloadTexture(spaceshipImage);
    for (int i = 0; i < 4; i++) {
        UnloadTexture(backgrounds[i]);
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
