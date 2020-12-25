#include "Player.h"

#include <algorithm>

#include "core/Game.h"
#include "core/constants.h"

void Player::update(float t)
{
    stateTime += t;

    float lastX = x;
    float lastY = y;
    float lastVelocityY = velocity.y;

    velocity.x = PLAYER_SPEED * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    velocity.y += PLAYER_GRAVITY * t;

    looksRight = velocity.x > 0 ? true : velocity.x < 0 ? false : looksRight;

    x = std::clamp(x + t * velocity.x, -PLAYER_COLLIDER.x, static_cast<float>(LEVEL_WIDTH - TILE_DIMENSIONS + PLAYER_COLLIDER.x) - 0.001f);
    y = y + t * velocity.y;

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
            Game::getLevel().collides(feetCenter.x - PLAYER_COLLIDER.width / 2, feetCenter.y) ||
            Game::getLevel().collides(feetCenter.x + PLAYER_COLLIDER.width / 2, feetCenter.y)
        )
    )
    {
        y = floor(y / TILE_DIMENSIONS) * TILE_DIMENSIONS;
        velocity.y = 0;
    }
    else if (velocity.x != 0)
    {
        if (velocity.x > 0)
        {
            if
            (
                Game::getLevel().collides(feetCenter.x + PLAYER_COLLIDER.width / 2, feetCenter.y) ||
                Game::getLevel().collides(feetCenter.x + PLAYER_COLLIDER.width / 2, feetCenter.y - PLAYER_COLLIDER.height)
            )
            {
                x = floor((x + PLAYER_COLLIDER.x + PLAYER_COLLIDER.width) / TILE_DIMENSIONS) * TILE_DIMENSIONS - PLAYER_COLLIDER.x - PLAYER_COLLIDER.width;
                velocity.x = 0;
            }
        }
        else
        {
            if
            (
                Game::getLevel().collides(feetCenter.x - PLAYER_COLLIDER.width / 2, feetCenter.y) ||
                Game::getLevel().collides(feetCenter.x - PLAYER_COLLIDER.width / 2, feetCenter.y - PLAYER_COLLIDER.height)
            )
            {
                x = ceil((x + PLAYER_COLLIDER.x) / TILE_DIMENSIONS) * TILE_DIMENSIONS - PLAYER_COLLIDER.x;
                velocity.x = 0;
            }
        }
    }

    if (velocity.y == 0 && lastVelocityY <= 0)
        if (velocity.x == 0)
            setState(Idle);
        else
            setState(Walking);
    else if (velocity.y < 0)
        setState(Jumping);
    else
        setState(Falling);
}

void Player::draw()
{
    switch (state)
    {
    case Idle:
        if (looksRight)
            Game::getView().drawSprite(Animation::get("anim_PlayerIdle_R").getCurrentSprite(stateTime, true), position);
        else
            Game::getView().drawSprite(Animation::get("anim_PlayerIdle_L").getCurrentSprite(stateTime, true), position);
        break;
    case Walking:
        if (looksRight)
            Game::getView().drawSprite(Animation::get("anim_PlayerWalk_R").getCurrentSprite(stateTime, true), position);
        else
            Game::getView().drawSprite(Animation::get("anim_PlayerWalk_L").getCurrentSprite(stateTime, true), position);
        break;
    case Jumping:
        if (looksRight)
            Game::getView().drawSprite(Sprite::get("spr_PlayerJump_R"), position);
        else
            Game::getView().drawSprite(Sprite::get("spr_PlayerJump_L"), position);
        break;
    case Falling:
        if (looksRight)
            Game::getView().drawSprite(Sprite::get("spr_PlayerFall_R"), position);
        else
            Game::getView().drawSprite(Sprite::get("spr_PlayerFall_L"), position);
        break;
    }
}

void Player::setState(State newState)
{
    if (state != newState)
    {
        stateTime = 0;
        state = newState;
    }
}
