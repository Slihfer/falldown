#pragma once

#include "bases.h"

#include <raylib.h>

#include "util/Timepoint.h"

enum class GhostPowerupState
{
    Spawn,
    Idle,
    Dissipate
};

class GhostPowerup :
    public virtual PositionalObject,
    public StateObject<GhostPowerupState>,
    public ColliderObject,
    public DestructibleObject
{
public:
    using State = GhostPowerupState;

public:
    GhostPowerup(Vector2 position);
    GhostPowerup(float x, float y);

public:
    void update();
    void draw();

public:
    static constexpr Rectangle COLLIDER{ 2, 2, 4, 4 };
};