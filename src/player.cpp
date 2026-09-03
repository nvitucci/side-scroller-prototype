#include "game_config.hpp"
#include "player.hpp"

Player::Player(Texture2D &spritesheet):
    position({100, 300}), velocity({0, 0}),
    // Actual player width and height can be scaled, do not have to be the same as in the spritesheet
    width(PLAYER_WIDTH / 2), height(PLAYER_HEIGHT / 2),
    state(IDLE),
    idleAnimation({{0, 0, PLAYER_WIDTH, PLAYER_HEIGHT}, 4})
{
    currentAnimation = &idleAnimation;
}

void Player::Update(const float deltaTime) {
    velocity.x = PLAYER_SPEED / 2;

    // Basic movements
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        velocity.y = -PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        velocity.y = PLAYER_SPEED;
    }

    // Update position
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Check screen boundaries
    if (position.x < 0)
        position.x = 0;
    const int SCREEN_BOUNDARY = 5000;
    if (position.x > SCREEN_BOUNDARY)
        position.x = SCREEN_BOUNDARY;

    // Update state animation
    switch (state) {
        case IDLE:
            currentAnimation = &idleAnimation;
            break;
        default:
            currentAnimation = &idleAnimation;
    }

    currentAnimation->Update(deltaTime);
}

void Player::Draw(const Texture2D &spritesheet) const {
    const Rectangle source = currentAnimation->GetCurrentFrame();
    const Rectangle destination = {position.x, position.y, width, height};

    const Vector2 origin = {0, 0};
    const float rotation = 0.0f;
    const Color tint = WHITE;

    DrawTexturePro(spritesheet, source, destination, origin, rotation, tint);
}

Rectangle Player::GetBounds() const {
    return {position.x, position.y, width, height};
}
