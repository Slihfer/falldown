#include "Blob.h"

#include "core/Game.h"
#include "draw/Animation.h"

Blob::Blob(Vector2 position) : Blob(position.x, position.y) {}

Blob::Blob(float x, float y) :
    looksLeft(GetRandomBool()),
    state(Spawning),
    stateTime(),
    position{ x, y },
    velocity{} {}

void Blob::update()
{
    switch (state)
    {
    case Spawning:
        if (stateTime.expired() > Animation::get("anim_BlobSpawn").getDuration())
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

void Blob::draw()
{
    switch (state)
    {
    case Spawning:
        Game::getView().drawSprite(Animation::get("anim_BlobSpawn").getCurrentSprite(stateTime.expired()), position, looksLeft);
        break;
    case Idle:
        Game::getView().drawSprite(Animation::get("anim_BlobIdle").getCurrentSprite(stateTime.expired(), true), position, looksLeft);
        break;
    case Walking:
        Game::getView().drawSprite(Animation::get("anim_BlobWalk").getCurrentSprite(stateTime.expired(), true), position, looksLeft);
        break;
    }
}

void Blob::setState(State newState)
{
    if (state != newState)
    {
        state = newState;
        stateTime.start();
    }
}

Rectangle Blob::getCollider()
{
    return { COLLIDER.x + x, COLLIDER.y + y, COLLIDER.width, COLLIDER.height };
}
