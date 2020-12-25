#pragma once

#include <raylib.h>

constexpr float PLAYER_SPEED = 48;
constexpr float PLAYER_GRAVITY = 96;
constexpr Rectangle PLAYER_COLLIDER{ 1.0f, 2.0f, 4.0f, 6.0f };

class Player
{
public:
    union
    {
        struct { float x, y; };
        Vector2 position;
    };

    Vector2 velocity;

    void update(float t);
    void draw();
};