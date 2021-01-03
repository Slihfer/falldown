#include "Blob.h"

#include "core/Game.h"
#include "core/constants.h"
#include "draw/Animation.h"
#include "draw/draw.h"
#include "util/collision.h"
#include "util/rectangle.h"

Blob::Blob(Vector2 position) :
    PositionalObject(position),
    KineticObject(),
    DirectionalObject(GetRandomBool()),
    StateObject(State::Spawn),
    ColliderObject(COLLIDER),
    DestructibleObject(),
    VoidDestructibleObject() {}


Blob::Blob(float x, float y) : Blob(Vector2{ x, y }) {}

void Blob::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    handleVoidAuraCollisions();

    switch (getState())
    {
    case State::Spawn:
        if (getStateTime().elapsed() >= Animation::get("anim_BlobSpawn").getDuration())
            setState(State::Walk);

        return;
    case State::Walk:
        if (!Game::getLevel().collides(x + COLLIDER.x + (looksLeft ? -EDGE_SENSE : COLLIDER.width + EDGE_SENSE), y + TILE_DIMENSIONS) ||
            Game::getLevel().collides(x + COLLIDER.x + (looksLeft ? -EDGE_SENSE : COLLIDER.width + EDGE_SENSE), y + COLLIDER.y))
        {
            setState(State::Turn);
            velocity.x = 0;
        }
        else
        {
            velocity.x = looksLeft ? -ACCELERATION : ACCELERATION;
        }

        break;

    case State::Turn:
        if (getStateTime().elapsed() >= Animation::get("anim_BlobTurn").getDuration())
        {
            setState(State::Walk);
            looksLeft = !looksLeft;
        }

        break;
    }

    x += velocity.x * Game::delta();

    Player& player = Game::getPlayer();
    if (CheckCollisionRecs(player.getCollider(), getCollider()))
        player.damage(KNOCKBACK * Vector2{ GetRectangleCenter(player.getCollider()).x < GetRectangleCenter(getCollider()).x ? -1.0f : 1.0f, 1.0f }, HIT_STUN);
}

void Blob::draw()
{
    switch (getState())
    {
    case State::Spawn:
        DrawSpriteWorld(Animation::get("anim_BlobSpawn").getCurrentSprite(getStateTime().elapsed()), position, looksLeft);
        break;
    case State::Turn:
        DrawSpriteWorld(Animation::get("anim_BlobTurn").getCurrentSprite(getStateTime().elapsed(), true), position, looksLeft);
        break;
    case State::Walk:
        DrawSpriteWorld(Animation::get("anim_BlobWalk").getCurrentSprite(getStateTime().elapsed(), true), position, looksLeft);
        break;
    }
}