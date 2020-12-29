#include "rectangle.h"

#include "util/vector.h"

Vector2 GetRectanglePosition(Rectangle rec)
{
    return { rec.x, rec.y };
}

Vector2 GetRectangleDimensions(Rectangle rec)
{
    return { rec.width, rec.height };
}

Vector2 GetRectangleCenter(Rectangle rec)
{
    return GetRectanglePosition(rec) + 0.5f * GetRectangleDimensions(rec);
}

Vector2 GetRectangleBottomRight(Rectangle rec)
{
    return GetRectanglePosition(rec) + GetRectangleDimensions(rec);
}

float GetRectangleRight(Rectangle rec)
{
    return rec.x + rec.width;
}

float GetRectangleBottom(Rectangle rec)
{
    return rec.y + rec.height;
}

Rectangle AssembleRectangle(Vector2 position, Vector2 dimensions)
{
    return { position.x, position.y, dimensions.x, dimensions.y };
}

Rectangle MoveRectangle(Rectangle rec, Vector2 offset)
{
    return { rec.x + offset.x, rec.y + offset.y, rec.width, rec.height };
}
