#include "Player.h"

#include <algorithm>

#include <raymath.h>

#include "core/Game.h"
#include "core/constants.h"
#include "draw/Animation.h"
#include "draw/drawText.h"

//TODO make time checking more general

void Player::update()
{
    float lastX = x;
    float lastY = y;
    float lastVelocityY = velocity.y;

    velocity.y += GRAVITY * Game::delta();
    velocity.y *= 1.0f - DRAG * Game::delta();

    if (hitStunTime.isExpired())
        velocity.x = SPEED * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));

    if (IsKeyReleased(KEY_K))
        jumpBoostEndTime.end();

    if (velocity.y != 0 && IsKeyPressed(KEY_K))
        jumpBuffer.start();

    if (hitStunTime.isExpired())
    {
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
        }
        else if (velocity.y < 0 && IsKeyDown(KEY_K) && jumpBoostStartTime.isExpired() && jumpBoostEndTime.isOngoing())
        {
            velocity.y = JUMP_SPEED;
        }
    }

    looksLeft = velocity.x < 0 ? true : velocity.x > 0 ? false : looksLeft;

    position = Vector2Add(position, Vector2Scale(velocity, Game::delta()));

    Vector2 feetCenter = { x + HALF_TILE_DIMENSIONS, y + TILE_DIMENSIONS };

    if (velocity.x != 0)
    {
        if (velocity.x > 0)
        {
            if
            (
                Game::getLevel().collides(feetCenter.x + COLLIDER.width / 2, feetCenter.y - COLLIDER.height) ||
                (y < TILE_DIMENSIONS - COLLIDER.y && Game::getLevel().collides(feetCenter.x + COLLIDER.width / 2, feetCenter.y))
            )
            {
                x = floor((x + COLLIDER.x + COLLIDER.width) / TILE_DIMENSIONS) * TILE_DIMENSIONS - COLLIDER.x - COLLIDER.width;
                velocity.x = 0;
            }
        }
        else
        {
            if
            (
                Game::getLevel().collides(feetCenter.x - COLLIDER.width / 2, feetCenter.y - COLLIDER.height) ||
                (y < TILE_DIMENSIONS - COLLIDER.y && Game::getLevel().collides(feetCenter.x - COLLIDER.width / 2, feetCenter.y))
            )
            {
                x = ceil((x + COLLIDER.x) / TILE_DIMENSIONS) * TILE_DIMENSIONS - COLLIDER.x;
                velocity.x = 0;
            }
        }
    }

    if
    (
        (
            !(fmodf(lastY, TILE_DIMENSIONS)) ||
            static_cast<int>(lastY / TILE_DIMENSIONS) != static_cast<int>(y / TILE_DIMENSIONS)
        ) && 
        (
            Game::getLevel().collides(feetCenter.x - COLLIDER.width / 2, feetCenter.y) ||
            Game::getLevel().collides(feetCenter.x + COLLIDER.width / 2, feetCenter.y)
        )
    )
    {
        y = floor(y / TILE_DIMENSIONS) * TILE_DIMENSIONS;
        velocity.y = 0;
        coyoteTime.start();
    }

    if (velocity.y == 0 && lastVelocityY >= 0)
        if (velocity.x == 0)
            setState(Idle);
        else
            setState(Walking);
    else
    {
        state = Airborn;
    }
}

void Player::draw()
{
    for (int i = 0; i < health; ++i)
        Game::getView().drawSpriteScreen(Sprite::get("spr_PlayerLife"), i * TILE_DIMENSIONS, 0);

    switch (state)
    {
    case Idle:
        Game::getView().drawSprite(Animation::get("anim_PlayerIdle").getCurrentSprite(stateTime.elapsed(), true), position, looksLeft);
        break;
    case Walking:
        Game::getView().drawSprite(Animation::get("anim_PlayerWalk").getCurrentSprite(stateTime.elapsed(), true), position, looksLeft);
        break;
    case Airborn:
        if (velocity.y <= SLOW_JUMP_THRESHOLD)
            Game::getView().drawSprite(Sprite::get("spr_PlayerFastJump"), position, looksLeft);
        else if (velocity.y <= JUMP_HOVER_THRESHOLD) //velocity.y < PLAYER_FALL_HOVER_THRESHOLD && velocity.y > PLAYER_JUMP_HOVER_THRESHOLD)
            Game::getView().drawSprite(Sprite::get("spr_PlayerSlowJump"), position, looksLeft);
        else if (velocity.y <= FALL_HOVER_THRESHOLD)
            Game::getView().drawSprite(Sprite::get("spr_PlayerHover"), position, looksLeft);
        else
            Game::getView().drawSprite(Sprite::get("spr_PlayerFall"), position, looksLeft);
        break;
    }
}

void Player::setState(State newState)
{
    if (state != newState)
    {
        state = newState;
        stateTime.start();
    }
}

void Player::damage(Vector2 origin, float knockback)
{
    if (!isInvulnerable())
    {
        --health;
        invulnerabilityTime.start();
        hitStunTime.start();

        velocity = Vector2Scale({ Vector2Normalize(Vector2Subtract(position, origin)).x, -1.0f }, knockback);
    }
}

bool Player::isInvulnerable()
{
    return invulnerabilityTime.isOngoing();
}

Rectangle Player::getCollider()
{
    return { COLLIDER.x + x, COLLIDER.y + y, COLLIDER.width, COLLIDER.height };
}
