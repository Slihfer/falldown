#pragma once

#include <raylib.h>

#include "util/Duration.h"
#include "util/random.h"

class Blob
{
public:
    enum State
    {
        Spawn,
        Idle,
        Walk
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
    Vector2 velocity;

public:
    Blob(Vector2 position);
    Blob(float x, float y);

public:
    void update();
    void draw();
    void destroy();

    void setState(State newState);
    Rectangle getCollider();

public:
    static constexpr float ACCELERATION = 14;
    static constexpr Rectangle COLLIDER{ 2, 5, 4, 3 };
    static constexpr float EDGE_SENSE = 1;
    static constexpr Vector2 KNOCKBACK{ 96.0f, -96.0f };
    static constexpr float HIT_STUN = 0.5f;
};