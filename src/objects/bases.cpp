#include "bases.h"

#include "core/Game.h"
#include "util/collision.h"

PositionalObject::PositionalObject(Vector2 position) : position(position) {}

PositionalObject::PositionalObject(float x, float y) : PositionalObject(Vector2{ x, y }) {}

KineticObject::KineticObject(Vector2 velocity) : PositionalObject({}), velocity(velocity) {}

void KineticObject::applyVelocity()
{
    position += velocity * Game::delta();
}

DirectionalObject::DirectionalObject(bool looksLeft) : looksLeft(looksLeft) {}

ColliderObject::ColliderObject(Rectangle collider) : PositionalObject({}), collider(collider) {}

Rectangle ColliderObject::getCollider()
{
    return AssembleCollider(position, collider);
}

void DestructibleObject::destroy()
{
    Game::flagDestruction();
}
