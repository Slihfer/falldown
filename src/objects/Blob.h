#pragma once

#include <raylib.h>

#include "util/Duration.h"
#include "util/random.h"

class Blob
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

    void setState(State newState);
    Rectangle getCollider();

public:
    static constexpr float SPEED = 14;
    static constexpr Rectangle COLLIDER{ 2, 5, 4, 3 };
    static constexpr float EDGE_SENSE = 1;
};