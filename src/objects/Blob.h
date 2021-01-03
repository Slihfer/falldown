#pragma once

#include "bases.h"

#include <raylib.h>

#include "util/Duration.h"
#include "util/random.h"

enum class BlobState
{
    Spawn,
    Turn,
    Walk
};

class Blob :
    public virtual PositionalObject,
    public KineticObject,
    public DirectionalObject,
    public StateObject<BlobState>,
    public virtual ColliderObject,
    public virtual DestructibleObject,
    public VoidDestructibleObject
{
public:
    using State = BlobState;

public:
    Blob(Vector2 position);
    Blob(float x, float y);

public:
    void update();
    void draw();

public:
    static constexpr float ACCELERATION = 14;
    static constexpr Rectangle COLLIDER{ 2, 5, 4, 3 };
    static constexpr float EDGE_SENSE = 1;
    static constexpr Vector2 KNOCKBACK{ 96.0f, -96.0f };
    static constexpr float HIT_STUN = 0.5f;
};