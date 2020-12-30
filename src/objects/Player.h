#pragma once

#include <raylib.h>

#include "util/Duration.h"
#include "core/constants.h"

class Player
{
public:
    enum State
    {
        Idle,
        Walk,
        Air,
    };

private:
    Duration jumpBuffer{ 0.1f };
    Duration coyoteTime{ 0.1f };
    Duration jumpBoostStartTime{ 0.05f };
    Duration jumpBoostEndTime{ 0.35f };
    Duration turnTime{ 0.05f };

    Duration hitStunTime{ 0.5f };
    Duration invulnerabilityTime{ 1 };
    Duration powerupTime{ 3.0f };

public:
    int health = 3;

    union
    {
        struct { float x, y; };
        Vector2 position{ (LEVEL_WIDTH - TILE_DIMENSIONS) / 2, LEVEL_HEIGHT - VIEW_MAX_PLAYER_DISTANCE };
    };
    Vector2 velocity;

    bool looksLeft = true;
    State state = Air;
    Timepoint stateTime;

    bool collisionEnabled = true;

public:
    void update();
    void draw();

    void setState(State newState);

    void damage(Vector2 knockback);
    void powerup();

    bool isInvulnerable();

    Rectangle getCollider();

public:
    static constexpr float ACCELERATION = 1600.0f;
    static constexpr float SPEED_THRESHOLD = 2.0f;
    static constexpr float GRAVITY = 256.0f;
    static constexpr Vector2 DRAG{ 2.0f, 2.0f };
    static constexpr Vector2 FRICTION{ 12.0f, 0.0f };
    static constexpr float JUMP_SPEED = -64.0f;
    static constexpr float SLOW_JUMP_THRESHOLD = -36.0f;
    static constexpr float JUMP_HOVER_THRESHOLD = -6.0f;
    static constexpr float FALL_HOVER_THRESHOLD = 10.0f;
    static constexpr Rectangle COLLIDER{ 2.0f, 2.0f, 4.0f, 6.0f };
};