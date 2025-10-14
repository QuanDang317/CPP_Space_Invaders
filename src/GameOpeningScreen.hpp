#ifndef GAME_OPENING_SCREEN_HPP
#define GAME_OPENING_SCREEN_HPP

#include "raylib.h"
#include <vector>

class GameOpeningScreen {
public:
    GameOpeningScreen();

    void Update(float deltaTime);
    void Draw();
    bool IsActive() const;

private:
    bool active;
    bool initialized;
    float time;
};

#endif // GAME_OPENING_SCREEN_HPP
