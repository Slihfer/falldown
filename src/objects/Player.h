#pragma once

#include <raylib.h>

#include "util/Duration.h"

class Player
{
public:
    enum State
    {
        Idle,
        Walking,
        Airborn,
    };

private:
    Duration jumpBuffer{ 0.1f };
    Duration coyoteTime{ 0.1f };
    Duration jumpBoostStartTime{ 0.05f };
    Duration jumpBoostEndTime{ 0.35f };

    Duration invulnerabilityTime{ 1 };

public:
    float health;

    union
    {
        struct { float x, y; };
        Vector2 position;
    };
    Vector2 velocity;

    bool looksLeft = true;
    State state = Airborn;
    float stateTime = 0;

public:
    void update();
    void draw();

    void setState(State newState);

    void damage(Vector2 origin);

    bool isInvulnerable();

    Rectangle getCollider();

public:
    static constexpr float SPEED = 64;
    static constexpr float GRAVITY = 256;
    static constexpr float DRAG = 1.5f;
    static constexpr float JUMP_SPEED = -64;
    static constexpr float SLOW_JUMP_THRESHOLD = -36;
    static constexpr float JUMP_HOVER_THRESHOLD = -6;
    static constexpr float FALL_HOVER_THRESHOLD = 10;
    static constexpr Rectangle COLLIDER{ 2.0f, 2.0f, 4.0f, 6.0f };
};