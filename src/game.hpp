#pragma once

#include "raylib.h"

#include "game_config.hpp"
#include "parallax.hpp"

#include <vector>

#include "player.hpp"

struct Game {
    Texture2D characterSheet;
    Texture2D environmentSheet;
    std::vector<ParallaxLayer> bgLayers;

    Camera2D camera;
    GameState state;

    Player player;
    std::vector<Rectangle> obstacles;

    Game();

    void CreateLevel();
    void Update(float deltaTime);
    void Draw() const;
    void HandleInput();

    ~Game();
    bool shouldClose() const;
};
