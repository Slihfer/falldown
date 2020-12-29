#include "Blob.h"

#include "core/Game.h"
#include "core/constants.h"
#include "draw/Animation.h"
#include "draw/draw.h"
#include "util/collision.h"

Blob::Blob(Vector2 position) : Blob(position.x, position.y) {}

Blob::Blob(float x, float y) :
    looksLeft(GetRandomBool()),
    state(Spawn),
    stateTime(),
    position{ x, y },
    velocity{} {}

void Blob::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    switch (state)
    {
    case Spawn:
        if (stateTime.elapsed() > Animation::get("anim_BlobSpawn").getDuration())
            setState(Walk);

        return;
    case Walk:
        if (!Game::getLevel().collides(x + COLLIDER.x + (looksLeft ? -EDGE_SENSE : COLLIDER.width + EDGE_SENSE), y + TILE_DIMENSIONS) ||
            Game::getLevel().collides(x + COLLIDER.x + (looksLeft ? -EDGE_SENSE : COLLIDER.width + EDGE_SENSE), y + COLLIDER.y))
        {
            setState(Idle);
            velocity.x = 0;
        }
        else
        {
            velocity.x = looksLeft ? -ACCELERATION : ACCELERATION;
        }

        break;

    case Idle:
        if (stateTime.elapsed() > Animation::get("anim_BlobIdle").getDuration())
        {
            setState(Walk);
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
    case Spawn:
        DrawSpriteWorld(Animation::get("anim_BlobSpawn").getCurrentSprite(stateTime.elapsed()), position, looksLeft);
        break;
    case Idle:
        DrawSpriteWorld(Animation::get("anim_BlobIdle").getCurrentSprite(stateTime.elapsed(), true), position, looksLeft);
        break;
    case Walk:
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
    return AssembleCollider(position, COLLIDER);
}
