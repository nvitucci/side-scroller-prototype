#include "animation.hpp"

#include "raylib.h"

Animation::Animation(Rectangle firstFrame, int frameCount):
    frame(firstFrame), frameCount(frameCount), currentFrame(0), timer(0)
{

}

void Animation::Update(float deltaTime) {
    timer += deltaTime * ANIMATION_SPEED;

    // Loop animation
    if (timer >= 1.0f) {
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

Rectangle Animation::GetCurrentFrame() const {
    return {
        frame.x + (frame.width * currentFrame),
        frame.y,
        frame.width,
        frame.height
    };
}
