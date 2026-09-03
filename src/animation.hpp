#pragma once

#include "raylib.h"

#include "game_config.hpp"

struct Animation {
    Rectangle frame;

    int frameCount;
    int currentFrame;
    float timer;

    Animation(Rectangle firstFrame, int frameCount);
    void Update(float deltaTime);
    Rectangle GetCurrentFrame() const;
};

