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

    while (!game.shouldClose()) {
        const float deltaTime = GetFrameTime();

        game.HandleInput();
        game.Update(deltaTime);
        game.Draw();
    }

    return 0;
}