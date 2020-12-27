#pragma once

#include <raylib.h>

struct CollisionInfo
{
    bool hit;
    bool unstuckX;
};

Rectangle AssembleCollisionRec(Vector2 position, Rectangle collider);
CollisionInfo GetCollisionInfo(Vector2 position1, Vector2 position2, Rectangle collider1, Rectangle collider2, Vector2 speed1 = {}, Vector2 speed2 = {});