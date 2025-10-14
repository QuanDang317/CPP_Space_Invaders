#pragma once
#include <raylib.h>

class GameOver {
public:
    GameOver() : restartRequested(false) {} 

    void Update();
    void Draw();

    bool IsRestartRequested() const { return restartRequested; } // Kiểm tra xem có yêu cầu khởi động lại không
    void Reset() { restartRequested = false; } // Đặt lại cờ khởi động lại

private:
    bool restartRequested; // Cờ để kiểm tra xem người chơi có yêu cầu khởi động lại không
};
