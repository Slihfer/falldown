#pragma once

#include "bases.h"

#include <raylib.h>

#include "util/Duration.h"
#include "core/constants.h"

enum class PlayerState
{
    Idle,
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
    Duration voidPowerupTime{ 3.0f };

public:
    int health = 3;

public:
    Player();

public:
    void update();
    void draw();

    void damage(Vector2 knockback, float hitStun);
    void ghostPowerup();
    void voidPowerup();

    bool isInvulnerable();

public:
    static constexpr float ACCELERATION = 1600.0f;
    static constexpr float SPEED_THRESHOLD = 2.0f;
    static constexpr float GRAVITY = 256.0f;
    static constexpr Vector2 DRAG{ 2.0f, 2.0f };
    static constexpr Vector2 FRICTION{ 12.0f, 0.0f };
    static constexpr float JUMP_SPEED = -64.0f;
    static constexpr float SLOW_JUMP_THRESHOLD = -36.0f;
    static constexpr float JUMP_HOVER_THRESHOLD = -6.0f;
    static constexpr float FALL_HOVER_THRESHOLD = 10.0f;
    static constexpr Rectangle COLLIDER{ 2.0f, 2.0f, 4.0f, 6.0f };
    static constexpr float GHOST_POWERUP_TIME = 5.0f;
};