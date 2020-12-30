#pragma once

#include <raylib.h>

#include "util/Duration.h"

class PositionalObject
{
public:
    union
    {
        struct { float x, y; };
        Vector2 position;
    };

    PositionalObject(Vector2 position);
    PositionalObject(float x, float y);
};

class KineticObject
{
public:
    Vector2 velocity;

    KineticObject(Vector2 velocity = {});
};

template <typename TState>
class StateObject
{
private:
    TState state;
    Duration stateTime;

public:
    StateObject(TState state) : state(state) {}

    void setState(TState newState)
    {
        if (state != newState)
        {
            state = newState;
            stateTime.start();
        }
    }

    const Duration& getStateTime()
    {
        return stateTime;
    }
};

class ColliderObject : public virtual PositionalObject
{
private:
    Rectangle collider;

public:
    ColliderObject(Rectangle collider);

    Rectangle getCollider();
};

class DestructibleObject
{
    void destroy();
};