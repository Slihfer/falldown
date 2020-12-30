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

Vector2 GetRectangleTopCenter(Rectangle rec)
{
    return GetRectanglePosition(rec) + Vector2{ 0.5f * rec.width, 0.0f };
}

Vector2 GetRectangleBottomCenter(Rectangle rec)
{
    return GetRectanglePosition(rec) + Vector2{ 0.5f * rec.width, rec.height };
}

Vector2 GetRectangleLeftCenter(Rectangle rec)
{
    return GetRectanglePosition(rec) + Vector2{ 0.0f, 0.5f * rec.height };
}

Vector2 GetRectangleRightCenter(Rectangle rec)
{
    return GetRectanglePosition(rec) + Vector2{ rec.width, 0.5f * rec.height };
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
