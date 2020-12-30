#include "Player.h"

#include <algorithm>

#include "core/Game.h"
#include "core/constants.h"
#include "draw/Animation.h"
#include "draw/draw.h"
#include "util/rectangle.h"

//TODO make time checking more general

void Player::update()
{
    float lastX = x;
    float lastY = y;
    float lastVelocityY = velocity.y;

    if (IsKeyUp(KEY_K))
        jumpBoostEndTime.end();

    if (state == Air && IsKeyPressed(KEY_K))
        jumpBuffer.start();

    if (hitStunTime.isExpired())
    {
        if (IsKeyDown(KEY_A) && velocity.x > 0 || IsKeyDown(KEY_D) && velocity.x < 0)
        {
            turnTime.start();
            velocity.x = 0;
        }

        if (turnTime.isExpired())
            velocity.x += ACCELERATION * Game::delta() * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));

        if (((velocity.y == 0 && lastVelocityY >= 0) ||
            coyoteTime.isOngoing()) &&
            (IsKeyPressed(KEY_K) ||
                (jumpBuffer.isOngoing()) && IsKeyDown(KEY_K)))
        {
            velocity.y = JUMP_SPEED;
            coyoteTime.end();
            jumpBuffer.end();
            jumpBoostStartTime.start();
            jumpBoostEndTime.start();
            setState(Air);
        }
        else if (velocity.y < 0 && IsKeyDown(KEY_K) && jumpBoostStartTime.isExpired() && jumpBoostEndTime.isOngoing())
        {
            velocity.y = JUMP_SPEED;
        }
    }

    looksLeft = velocity.x < 0 ? true : velocity.x > 0 ? false : looksLeft;

    velocity.y += GRAVITY * Game::delta();
    velocity *= 1.0f - DRAG * Game::delta();
    
    if (state != Air || (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)))
        velocity *= 1.0f - FRICTION * Game::delta();

    if (abs(velocity.x) < SPEED_THRESHOLD)
        velocity.x = 0;

    position += velocity * Game::delta();

    Level& level = Game::getLevel();

    if (collisionEnabled ?
        level.handleCollision(position, COLLIDER, velocity).y < 0 :
        (level.handleWallsCollision(position, COLLIDER, velocity), false))
    {
        coyoteTime.start();

        if (velocity.x == 0)
            setState(Idle);
        else
            setState(Walk);
    }
    else
    {
        setState(Air);
    }

    if (!collisionEnabled && powerupTime.isExpired() && !level.collides(getCollider()))
        collisionEnabled = true;
}

void Player::draw()
{
    for (int i = 0; i < health; ++i)
        DrawSpriteScreen(Sprite::get("spr_PlayerLife"), i * TILE_DIMENSIONS, 0);

    switch (state)
    {
    case Idle:
        DrawSpriteWorld(Animation::get("anim_PlayerIdle").getCurrentSprite(stateTime.elapsed(), true), position, looksLeft);
        break;
    case Walk:
        DrawSpriteWorld(Animation::get("anim_PlayerWalk").getCurrentSprite(stateTime.elapsed(), true), position, looksLeft);
        break;
    case Air:
        if (velocity.y <= SLOW_JUMP_THRESHOLD)
            DrawSpriteWorld(Sprite::get("spr_PlayerFastJump"), position, looksLeft);
        else if (velocity.y <= JUMP_HOVER_THRESHOLD) //velocity.y < PLAYER_FALL_HOVER_THRESHOLD && velocity.y > PLAYER_JUMP_HOVER_THRESHOLD)
            DrawSpriteWorld(Sprite::get("spr_PlayerSlowJump"), position, looksLeft);
        else if (velocity.y <= FALL_HOVER_THRESHOLD)
            DrawSpriteWorld(Sprite::get("spr_PlayerHover"), position, looksLeft);
        else
            DrawSpriteWorld(Sprite::get("spr_PlayerFall"), position, looksLeft);
        break;
    }

    if (!collisionEnabled)
        DrawSpriteWorld(Sprite::get("spr_PlayerAura"), position - HALF_TILE_DIMENSIONS, false, true);
}

void Player::setState(State newState)
{
    if (state != newState)
    {
        state = newState;
        stateTime.start();
    }
}

void Player::damage(Vector2 knockback)
{
    if (!isInvulnerable())
    {
        --health;
        invulnerabilityTime.start();
        hitStunTime.start();

        velocity = knockback;
    }
}

void Player::powerup()
{
    collisionEnabled = false;
    powerupTime.start();
}

bool Player::isInvulnerable()
{
    return invulnerabilityTime.isOngoing();
}

Rectangle Player::getCollider()
{
    return { COLLIDER.x + x, COLLIDER.y + y, COLLIDER.width, COLLIDER.height };
}