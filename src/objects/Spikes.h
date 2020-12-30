#pragma once

#include <raylib.h>

#include "util/Timepoint.h"
#include "bases.h"

enum class SpikesState
{
    Idle,
    Poke,
    Out,
    Retract
};

class Spikes :
    public virtual PositionalObject,
    public ColliderObject,
    public StateObject<SpikesState>,
    public DestructibleObject
{
public:
    using State = SpikesState;

public:
    Spikes(Vector2 position);
    Spikes(float x, float y);

public:
    void update();
    void draw();

public:
    static constexpr Rectangle COLLIDER{ 1, 0, 6, 8 };
    static constexpr float ACTIVATION_DISTANCE = 24.0f;
    static constexpr float COOLDOWN = 0.6f;
    static constexpr float OUT_TIME = 2.0f;
    static constexpr Vector2 KNOCKBACK{ 96.0f, -96.0f };
    static constexpr float HIT_STUN = 0.5f;
};