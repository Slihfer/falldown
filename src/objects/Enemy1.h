#pragma once

#include <raylib.h>

#include "util/random.h"

class Enemy1
{
public:
    enum State
    {
        Spawning,
        Idle,
        Walking
    };

private:
    bool looksLeft = GetRandomBool();
    State state = Spawning;
    float stateTime = 0;

public:
    union
    {
        struct { float x, y; };
        Vector2 position;
    };
    Vector2 velocity;

public:
    void update();
    void draw();

    void setState(State newState);
    Rectangle getCollider();

public:
    static constexpr float SPEED = 16;
    static constexpr Rectangle COLLIDER{ 2, 5, 4, 3 };
    static constexpr float EDGE_SENSE = 1;
};