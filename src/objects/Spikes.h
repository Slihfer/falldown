#pragma once

#include <raylib.h>

#include "util/Timepoint.h"

class Spikes
{
public:
    enum State
    {
        Idle,
        Poke,
        Out,
        Retract
    };

private:
    State state;
    Timepoint stateTime;

public:
    union
    {
        struct { float x, y; };
        Vector2 position;
    };

public:
    Spikes(Vector2 position);
    Spikes(float x, float y);

public:
    void update();
    void draw();
    void destroy();

    void setState(State newState);
    Rectangle getCollider();

public:
    static constexpr Rectangle COLLIDER{ 1, 0, 6, 8 };
    static constexpr float ACTIVATION_DISTANCE = 24.0f;
    static constexpr float COOLDOWN = 0.6f;
    static constexpr float OUT_TIME = 2.0f;
    static constexpr float KNOCKBACK = 64.0f;
};