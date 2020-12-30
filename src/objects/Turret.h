#pragma once

#include "bases.h"

#include <raylib.h>

#include "util/Timepoint.h"

enum class TurretState
{
    Idle,
    Charge,
    Shoot,
    Retract
};

class Turret :
    public virtual PositionalObject,
    public DirectionalObject,
    public StateObject<TurretState>,
    public DestructibleObject
{
private:
    Rectangle collider;

public:
    using State = TurretState;

public:
    Turret(Vector2 position, bool looksLeft);
    Turret(float x, float y, bool looksLeft);

public:
    void update();
    void draw();

public:
    static constexpr float COLLIDER_OFFSET = 3.0f;
    static constexpr float COLLIDER_HEIGHT = 2.0f;
    static constexpr float ACTIVATION_DISTANCE = 8.0f;
    static constexpr float CHARGE_TIME = 2.0f;
    static constexpr float SHOOT_TIME = 2.0f;
    static constexpr Vector2 KNOCKBACK{ 0.0f, -128.0f };
    static constexpr float HIT_STUN = 0.5f;
};