#include "game.hpp"

#include <cmath>

#include "game_config.hpp"

Game::Game():
    state(PLAYING), player(characterSheet)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Side scroller prototype");

    InitAudioDevice();              // Initialize audio device

    music = LoadMusicStream("assets/music.mp3");

    PlayMusicStream(music);

    float pan = 0.0f;               // Default audio pan center [-1.0f..1.0f]
    SetMusicPan(music, pan);

    float volume = 0.8f;            // Default audio volume [0.0f..1.0f]
    SetMusicVolume(music, volume);

    SetTargetFPS(60);

    characterSheet = LoadTexture("assets/spaceship_sprite.png");
    environmentSheet = LoadTexture("assets/Tile_31.png");

    // Layers for the background parallax effect
    bgLayers = {
        {LoadTexture("assets/1.png"), 0.1f, {0, 0}},
        {LoadTexture("assets/2.png"), 0.3f, {0, 0}},
        {LoadTexture("assets/3.png"), 0.5f, {0, 0}},
        {LoadTexture("assets/4.png"), 0.8f, {0, 0}}
    };

    camera.target = {0, 0};
    camera.offset = {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 3.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    CreateLevel();
}

void Game::CreateLevel() {
    // Obstacles
    obstacles.push_back({0, 600, 800, 120});
    obstacles.push_back({900, 550, 400, 120});
    obstacles.push_back({1400, 500, 300, 120});
    obstacles.push_back({1800, 450, 200, 20});
    obstacles.push_back({2100, 400, 200, 20});
    obstacles.push_back({2400, 350, 500, 120});
    obstacles.push_back({300, 450, 100, 20});
    obstacles.push_back({500, 350, 100, 20});
    obstacles.push_back({700, 250, 100, 20});
}

void Game::Update(float deltaTime) {
    UpdateMusicStream(music);

    if (state != PLAYING) {
        return;
    }

    player.Update(deltaTime);
    camera.target = {player.position.x, player.position.y - 100};

    // TODO: doesn't work, check logic
    if (IsKeyDown(KEY_P)) {
        state = PAUSED;
        PauseMusicStream(music);
    }

    state = PLAYING;
    ResumeMusicStream(music);

    // "Move" the background layers in the opposite direction of the player,
    // to obtain a "parallax" effect
    for (auto &layer: bgLayers) {
        layer.offset.x = -player.position.x * layer.speed;
        layer.offset.y = -player.position.y * layer.speed;
    }
}

void Game::Draw() const {
    BeginDrawing();
    ClearBackground(SKYBLUE);

    for (const auto &layer: bgLayers) {
        // fmod returns the floating point reminder of dividend/divisor
        // Used here to avoid repetition of the texture
        const int x = static_cast<int>(std::fmod(layer.offset.x, layer.texture.width));
        // const int x = 0;
        const int y = static_cast<int>(std::fmod(layer.offset.y, layer.texture.height));
        // const int y = 0;

        DrawTexture(layer.texture, x, y, WHITE);
        // DrawTexture(layer.texture, x, y + layer.texture.height, WHITE);
    }

    BeginMode2D(camera);

    for (const auto obstacle: obstacles) {
        // Tiles for platforms
        Rectangle source = {0, 64, 32, 32};

        // Note: Each platform can have its own width
        for (float x = obstacle.x; x < obstacle.x + obstacle.width; x += 32) {
            for (float y = obstacle.y; y < obstacle.y + obstacle.height; y += 32) {
                DrawTexturePro(environmentSheet, source, {x, y, 32, 32}, {0, 0}, 0, WHITE);
            }
        }
    }

    player.Draw(characterSheet);
    EndMode2D();

    DrawText("A/D: Move | Space: Jump | J: Attack | E: Interact", 20, SCREEN_HEIGHT - 30, 16, WHITE);

    EndDrawing();
}

void Game::HandleInput() {
    if (state == PAUSED && IsKeyDown(KEY_P)) {
        state = PLAYING;
    }
}

Game::~Game() {
    UnloadTexture(characterSheet);
    UnloadTexture(environmentSheet);

    for (auto &layer: bgLayers) {
        UnloadTexture(layer.texture);
    }

    UnloadMusicStream(music);   // Unload music stream buffers from RAM

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();
}

bool Game::shouldClose() const {
    return WindowShouldClose();
}