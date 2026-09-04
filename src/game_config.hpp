#pragma once

inline constexpr int SCREEN_WIDTH = 1280;
inline constexpr int SCREEN_HEIGHT = 720;

// Player sprite dimensions
inline constexpr int PLAYER_WIDTH = 192;
inline constexpr int PLAYER_HEIGHT = 192;

inline constexpr float PLAYER_SPEED = 100.0f;
inline constexpr float ANIMATION_SPEED = 10.0f;

enum GameState {
    PLAYING,
    PAUSED,
    GAME_OVER,
};

enum PlayerState {
    IDLE,
    RUNNING,
    JUMPING,
    ATTACKING,
};