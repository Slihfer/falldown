#include "collision.h"

Rectangle AssembleCollisionRec(Vector2 position, Rectangle collider)
{
    return { position.x + collider.x, position.y + collider.y, collider.width, collider.height };
}

CollisionInfo GetCollisionInfo(Vector2 position1, Vector2 position2, Rectangle collider1, Rectangle collider2, Vector2 speed1, Vector2 speed2)
{
    if (Rectangle rec1 = AssembleCollisionRec(position1, collider1),
                  rec2 = AssembleCollisionRec(position2, collider2);
        CheckCollisionRecs(rec1, rec2))
    {
        return {};
    }

    return {};
}