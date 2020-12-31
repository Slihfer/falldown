#pragma once

#include "bases.h"

#include <raylib.h>

#include "util/Timepoint.h"

enum class VoidPowerupState
{
    Spawn,
    Idle,
    Dissipate
};

class VoidPowerup :
    public virtual PositionalObject,
    public StateObject<VoidPowerupState>,
    public ColliderObject,
    public DestructibleObject
{
public:
    using State = VoidPowerupState;

public:
    VoidPowerup(Vector2 position);
    VoidPowerup(float x, float y);

public:
    void update();
    void draw();

public:
    static constexpr Rectangle COLLIDER{ 2, 2, 4, 4 };
};