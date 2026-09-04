#include <thread>
#include <chrono>

#include "raylib.h"

#include "game.hpp"

int main()
{
    // Game main loop (using delta time as "time / FPS"):
    //
    // - Handle input
    // - Update status
    // - Redraw

    Game game;

    // TODO: Temporary, to take video
    // using namespace std::this_thread;     // sleep_for, sleep_until
    // using namespace std::chrono_literals;
    // sleep_for(20s);

    while (!game.shouldClose()) {
        const float deltaTime = GetFrameTime();

        game.HandleInput();
        game.Update(deltaTime);
        game.Draw();
    }

    return 0;
}