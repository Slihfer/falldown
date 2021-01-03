#pragma once

#include "bases.h"

#include <raylib.h>

#include "util/Duration.h"
#include "core/constants.h"

enum class PlayerState
{
    Turn,
    Walk,
    Air,
};

class Player :
    public virtual PositionalObject,
    public KineticObject,
    public DirectionalObject,
    public StateObject<PlayerState>,
    public ColliderObject
{
public:
    using State = PlayerState;

private:
    Duration jumpBuffer{ 0.1f };
    Duration coyoteTime{ 0.1f };
    Duration jumpBoostStartTime{ 0.05f };
    Duration jumpBoostEndTime{ 0.35f };
    Duration turnTime{ 0.05f };

    Duration hitStunTime{ 0.0f };
    Duration invulnerabilityTime{ 0.0f };
    Duration voidPowerupTime{ 5.0f };

public:
    int health = 3;

public:
    Player();

private:
    void die();

public:
    void update();
    void draw();

    void damage(Vector2 knockback, float hitStun);
    void ghostPowerup();
    void voidPowerup();

    bool isInvulnerable();
    bool hasVoidPowerup();

public:
    static constexpr float ACCELERATION = 1200.0f;
    static constexpr float SPEED_THRESHOLD = 2.0f;
    static constexpr float GRAVITY = 256.0f;
    static constexpr Vector2 DRAG{ 2.0f, 2.0f };
    static constexpr Vector2 FRICTION{ 12.0f, 0.0f };
    static constexpr float JUMP_SPEED = -64.0f;
    static constexpr float SLOW_JUMP_THRESHOLD = -36.0f;
    static constexpr float JUMP_HOVER_THRESHOLD = -6.0f;
    static constexpr float FALL_HOVER_THRESHOLD = 10.0f;
    static constexpr Rectangle COLLIDER{ 2.0f, 2.0f, 4.0f, 6.0f };
    static constexpr float GHOST_POWERUP_TIME = 10.0f;
    static constexpr float VOID_AURA_RADIUS = 14.0f;
};