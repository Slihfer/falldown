#pragma once

#include <raylib.h>

#include "util/Timepoint.h"

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

class KineticObject : public virtual PositionalObject
{
public:
    Vector2 velocity;

    KineticObject(Vector2 velocity = {});

    void applyVelocity();
};

class DirectionalObject
{
public:
    bool looksLeft;

    DirectionalObject(bool looksLeft = false);
};

template <typename TState>
class StateObject
{
private:
    TState state;
    Timepoint stateTime;

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

    const TState& getState()
    {
        return state;
    }

    bool isState(TState otherState)
    {
        return state == otherState;
    }

    const Timepoint& getStateTime()
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
public:
    void destroy();
};



class VoidDestructibleObject :
    public virtual PositionalObject,
    public virtual ColliderObject,
    public virtual DestructibleObject
{
public:
    VoidDestructibleObject();

    void handleVoidAuraCollisions();
};