#include "Enemy1.h"

#include "core/Game.h"

void Enemy1::update()
{
    switch (state)
    {
    case Spawning:
        if (stateTime > Animation::get("anim_Enemy1Spawn").getDuration())
            setState(Walking);

        return;
    case Walking:
        velocity.x = looksLeft ? -SPEED : SPEED;

    case Idle:
        if (!Game::getPlayer().isInvulnerable() &&
            CheckCollisionRecs(
                { COLLIDER.x + x, COLLIDER.y + y, COLLIDER.width, COLLIDER.height },
                Game::getPlayer().getCollider()))
            Game::getPlayer().damage(position);

        break;
    }

    x += velocity.x * Game::delta();
}

void Enemy1::draw()
{
    switch (state)
    {
    case Spawning:
        Game::getView().drawSprite(Animation::get("anim_Enemy1Spawn").getCurrentSprite(stateTime), position, looksLeft);
        break;
    case Idle:
        Game::getView().drawSprite(Animation::get("anim_Enemy1Idle").getCurrentSprite(stateTime), position, looksLeft);
        break;
    case Walking:
        Game::getView().drawSprite(Animation::get("anim_Enemy1Walking").getCurrentSprite(stateTime), position, looksLeft);
        break;
    }
}

void Enemy1::setState(State newState)
{
    if (state != newState)
    {
        state = newState;
        stateTime = 0;
    }
}

Rectangle Enemy1::getCollider()
{
    return { COLLIDER.x + x, COLLIDER.y + y, COLLIDER.width, COLLIDER.height };
}
