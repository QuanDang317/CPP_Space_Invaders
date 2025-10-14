#include "GameOpeningScreen.hpp"
#include <cstdlib>

GameOpeningScreen::GameOpeningScreen() {
    active = true;
    time = 0.0f;
    initialized = false;
}

void GameOpeningScreen::Update(float deltaTime) {
    if (!active) return;

    time += deltaTime;

    if (IsKeyPressed(KEY_ENTER))
        active = false;
}

void GameOpeningScreen::Draw() {
    if (!active) return;

    const char* title = "SPACE INVADERS";
    const char* prompt = "PRESS ENTER TO START";
    const char* menu = "MENU :";
    const char* moveGuideRight = "-> : MOVE RIGHT";
    const char* movdeGuideLeft = "<- : MOVE LEFT ";
    const char* moveGuideShoot = "SPACE : SHOOT";
    const char* moveGuidePause = "P : PAUSE/RESUME";

    int titleFontSize = 70;          // Kích thước dòng chữ "SPACE INVADERS"
    int promptFontSize = 30;         // Kích thước dòng chữ "PRESS ENTER TO START"
    int menuFontSize = 25;           // Kích thước dòng chữ "MENU :"
    int moveGuideRightFontSize = 25; // Kích thước dòng chữ "-> : MOVE RIGHT"
    int moveGuideLeftFontSize = 25;  // Kích thước dòng chữ "<- : MOVE LEFT"
    int moveGuideShootFontSize = 25; // Kích thước dòng chữ "SPACE : SHOOT"
    int moveGuidePauseFontSize = 25; // Kích thước dòng chữ "P : PAUSE/RESUME"

    int titleWidth = MeasureText(title, titleFontSize);
    int promptWidth = MeasureText(prompt, promptFontSize);

    int menuWidth = MeasureText(menu,menuFontSize);
    int moveGuideRightWidth = MeasureText(moveGuideRight,moveGuideRightFontSize);
    int movdeGuideLeftWidth = MeasureText(movdeGuideLeft,moveGuideLeftFontSize);
    int moveGuideShootWidth = MeasureText(moveGuideShoot,moveGuideShootFontSize);
    int moveGuidePauseWidth = MeasureText(moveGuidePause,moveGuidePauseFontSize);

    float centerX = GetScreenWidth() / 2.0f;
    float centerY = GetScreenHeight() / 2.0f;

    DrawText(title, centerX - titleWidth / 2, centerY - 200, titleFontSize, YELLOW);
    DrawText(prompt, centerX - promptWidth / 2, centerY - 50, promptFontSize, WHITE);

    DrawText(menu, centerX - menuWidth / 2, centerY + 50, menuFontSize, WHITE);
    DrawText(movdeGuideLeft, centerX - movdeGuideLeftWidth / 2, centerY + 90, moveGuideLeftFontSize, WHITE);
    DrawText(moveGuideRight, centerX - moveGuideRightWidth / 2, centerY + 130, moveGuideRightFontSize, WHITE);
    DrawText(moveGuideShoot, centerX - moveGuideShootWidth / 2, centerY + 170, moveGuideShootFontSize, WHITE);
    DrawText(moveGuidePause, centerX - moveGuidePauseWidth / 2, centerY + 210, moveGuidePauseFontSize, WHITE);
}

bool GameOpeningScreen::IsActive() const {
    return active;
}
