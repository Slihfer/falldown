#pragma once

#include <raylib.h>

#include "util/Timepoint.h"

class Powerup
{
public:
    enum State
    {
        Spawn,
        Idle,
        Dissipate
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
    Powerup(Vector2 position);
    Powerup(float x, float y);

public:
    void update();
    void draw();
    void destroy();

    void setState(State newState);
    Rectangle getCollider();

public:
    static constexpr Rectangle COLLIDER{ 2, 2, 4, 4 };
};