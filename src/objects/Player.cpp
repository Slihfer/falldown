#include "Player.h"

#include <algorithm>

#include "core/Game.h"
#include "core/constants.h"
#include "draw/Animation.h"

//TODO make time checking more general

void Player::update()
{
    float lastX = x;
    float lastY = y;
    float lastVelocityY = velocity.y;

    velocity.x = SPEED * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    velocity.y += GRAVITY * Game::delta();
    velocity.y *= 1.0f - DRAG * Game::delta();

    looksLeft = velocity.x < 0 ? true : velocity.x > 0 ? false : looksLeft;

    x = std::clamp(x + Game::delta() * velocity.x, -COLLIDER.x, static_cast<float>(LEVEL_WIDTH - TILE_DIMENSIONS + COLLIDER.x) - 0.001f);
    y = y + Game::delta() * velocity.y;

    if (x == lastX)
        velocity.x = 0;

    Vector2 feetCenter = { x + HALF_TILE_DIMENSIONS, y + TILE_DIMENSIONS };

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
    else if (velocity.x != 0)
    {
        if (velocity.x > 0)
        {
            if
            (
                Game::getLevel().collides(feetCenter.x + COLLIDER.width / 2, feetCenter.y) ||
                Game::getLevel().collides(feetCenter.x + COLLIDER.width / 2, feetCenter.y - COLLIDER.height)
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
                Game::getLevel().collides(feetCenter.x - COLLIDER.width / 2, feetCenter.y) ||
                Game::getLevel().collides(feetCenter.x - COLLIDER.width / 2, feetCenter.y - COLLIDER.height)
            )
            {
                x = ceil((x + COLLIDER.x) / TILE_DIMENSIONS) * TILE_DIMENSIONS - COLLIDER.x;
                velocity.x = 0;
            }
        }
    }

    if (IsKeyReleased(KEY_K))
        jumpBoostEndTime.end();

    if (velocity.y != 0 && IsKeyPressed(KEY_K))
        jumpBuffer.start();

    if (((velocity.y == 0 && lastVelocityY >= 0) ||
        coyoteTime.isRunning()) &&
        (IsKeyPressed(KEY_K) ||
        (jumpBuffer.isRunning()) && IsKeyDown(KEY_K)))
    {
        velocity.y = JUMP_SPEED;
        coyoteTime.end();
        jumpBuffer.end();
        jumpBoostStartTime.start();
        jumpBoostEndTime.start();
    }
    else if (velocity.y < 0 && IsKeyDown(KEY_K) && jumpBoostStartTime.isExpired() && jumpBoostEndTime.isRunning())
    {
        velocity.y = JUMP_SPEED;
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
    switch (state)
    {
    case Idle:
        Game::getView().drawSprite(Animation::get("anim_PlayerIdle").getCurrentSprite(stateTime.expired(), true), position, looksLeft);
        break;
    case Walking:
        Game::getView().drawSprite(Animation::get("anim_PlayerWalk").getCurrentSprite(stateTime.expired(), true), position, looksLeft);
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

void Player::damage(Vector2 origin)
{
    --health;
    invulnerabilityTime.start();
}

bool Player::isInvulnerable()
{
    return invulnerabilityTime.isRunning();
}

Rectangle Player::getCollider()
{
    return { COLLIDER.x + x, COLLIDER.y + y, COLLIDER.width, COLLIDER.height };
}
