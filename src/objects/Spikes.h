#pragma once

#include <raylib.h>

#include "util/Timepoint.h"
#include "bases.h"

enum class SpikesState
{
    Turn,
    Poke,
    Out,
    Retract
};

class Spikes :
    public virtual PositionalObject,
    public virtual ColliderObject,
    public StateObject<SpikesState>,
    public virtual DestructibleObject,
    public VoidDestructibleObject
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
    static constexpr Rectangle COLLIDER{ 1, 2, 6, 6 };
    static constexpr float ACTIVATION_DISTANCE = 24.0f;
    static constexpr float COOLDOWN = 0.6f;
    static constexpr float OUT_TIME = 0.8f;
    static constexpr Vector2 KNOCKBACK{ 96.0f, -96.0f };
    static constexpr float HIT_STUN = 0.5f;
};