#pragma once

#include <raylib.h>

Vector2 GetRectanglePosition(Rectangle rec);
Vector2 GetRectangleDimensions(Rectangle rec);
Vector2 GetRectangleCenter(Rectangle rec);
Vector2 GetRectangleBottomRight(Rectangle rec);
float GetRectangleRight(Rectangle rec);
float GetRectangleBottom(Rectangle rec);
Rectangle AssembleRectangle(Vector2 position, Vector2 dimensions);
Rectangle MoveRectangle(Rectangle rec, Vector2 offset);