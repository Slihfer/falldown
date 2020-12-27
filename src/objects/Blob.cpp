#include "Blob.h"

#include "core/Game.h"
#include "core/constants.h"
#include "draw/Animation.h"
#include "draw/draw.h"

Blob::Blob(Vector2 position) : Blob(position.x, position.y) {}

Blob::Blob(float x, float y) :
    looksLeft(GetRandomBool()),
    state(Spawning),
    stateTime(),
    position{ x, y },
    velocity{} {}

void Blob::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    switch (state)
    {
    case Spawning:
        if (stateTime.elapsed() > Animation::get("anim_BlobSpawn").getDuration())
            setState(Walking);

        return;
    case Walking:
        if (!Game::getLevel().collides(x + COLLIDER.x + (looksLeft ? -EDGE_SENSE : COLLIDER.width + EDGE_SENSE), y + TILE_DIMENSIONS) ||
            Game::getLevel().collides(x + COLLIDER.x + (looksLeft ? -EDGE_SENSE : COLLIDER.width + EDGE_SENSE), y + COLLIDER.y))
        {
            setState(Idle);
            velocity.x = 0;
        }
        else
        {
            velocity.x = looksLeft ? -SPEED : SPEED;
        }

        break;

    case Idle:
        if (stateTime.elapsed() > Animation::get("anim_BlobIdle").getDuration())
        {
            setState(Walking);
            looksLeft = !looksLeft;
        }

        break;
    }

    x += velocity.x * Game::delta();

    if (CheckCollisionRecs(
            { COLLIDER.x + x, COLLIDER.y + y, COLLIDER.width, COLLIDER.height },
            Game::getPlayer().getCollider()))
        Game::getPlayer().damage(position, 64.0f);
}

void Blob::draw()
{
    switch (state)
    {
    case Spawning:
        DrawSpriteWorld(Animation::get("anim_BlobSpawn").getCurrentSprite(stateTime.elapsed()), position, looksLeft);
        break;
    case Idle:
        DrawSpriteWorld(Animation::get("anim_BlobIdle").getCurrentSprite(stateTime.elapsed(), true), position, looksLeft);
        break;
    case Walking:
        DrawSpriteWorld(Animation::get("anim_BlobWalk").getCurrentSprite(stateTime.elapsed(), true), position, looksLeft);
        break;
    }
}

void Blob::destroy()
{
    Game::flagDestruction();
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
