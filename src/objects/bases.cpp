#include "bases.h"

#include "core/Game.h"
#include "util/collision.h"

ColliderObject::ColliderObject(Rectangle collider) : collider(collider) {}

Rectangle ColliderObject::getCollider()
{
    return AssembleCollider(position, collider);
}

void DestructibleObject::destroy()
{
    Game::flagDestruction();
}

PositionalObject::PositionalObject(Vector2 position) : position(position) {}

PositionalObject::PositionalObject(float x, float y) : PositionalObject({ x, y }) {}

KineticObject::KineticObject(Vector2 velocity) : velocity(velocity) {}
