#pragma once

#include <cmath>
#include <vector>

#include "raylib.h"
#include "animation.hpp"

struct Player {
    Vector2 position;
    Vector2 velocity;

    float width;
    float height;

    PlayerState state;

    // Animation: {{xpos, ypos, width, height}, numOfSprites}}
    Animation idleAnimation;
    Animation* currentAnimation;

    Player(Texture2D &spritesheet);

    void Update(float deltaTime);
    void Draw(const Texture2D &spritesheet) const;

    Rectangle GetBounds() const;
};