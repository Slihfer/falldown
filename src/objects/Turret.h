#pragma once

#include <raylib.h>

#include "util/Timepoint.h"

/*
class Turret
{
public:
    enum State
    {
        Idle,
        Shoot,
        Retract
    };

private:
    bool looksLeft;
    State state;
    Timepoint stateTime;

public:
    union
    {
        struct { float x, y; };
        Vector2 position;
    };

public:
    Turret(Vector2 position);
    Turret(float x, float y);

public:
    void update();
    void draw();
    void destroy();

    void setState(State newState);
    Rectangle getCollider();

public:
    static constexpr Rectangle COLLIDER{ 0, 3, 8, 2 };
    static constexpr float ACTIVATION_DISTANCE = 8.0f;
    static constexpr float COOLDOWN = 2.0f;
    static constexpr float SHOOT_TIME = 2.0f;
    static constexpr float KNOCKBACK = 64.0f;
};
*/