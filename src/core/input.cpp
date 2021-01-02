#include "input.h"

#include "core/constants.h"

Rectangle GetLeftMouseControlArea()
{
    return { 0, 0, MOUSE_CONTROL_AREA * WINDOW_WIDTH, WINDOW_HEIGHT};
}

Rectangle GetRightMouseControlArea()
{
    return { (1.0f - MOUSE_CONTROL_AREA) * WINDOW_WIDTH, 0, MOUSE_CONTROL_AREA * WINDOW_WIDTH, WINDOW_HEIGHT };
}

void DrawMouseControlAreas()
{
    Rectangle left = GetLeftMouseControlArea();
    Rectangle right = GetRightMouseControlArea();

    Vector2 mousePosition = Game::getMousePosition();

    bool highlightLeft = CheckCollisionPointRec(mousePosition, left);
    bool highlightRight = CheckCollisionPointRec(mousePosition, right);

    if (highlightLeft)
        DrawRectangleRec(left, MOUSE_CONTROL_AREA_LEFT_COLOR);

    if (highlightRight)
        DrawRectangleRec(right, MOUSE_CONTROL_AREA_RIGHT_COLOR);
    
    if (!highlightLeft && !highlightRight)
    {
        DrawRectangleRec({ left.x + left.width, left.y, mousePosition.x - left.x - left.width, left.height }, MOUSE_CONTROL_AREA_LEFT_COLOR);
        DrawRectangleRec({ mousePosition.x, left.y, right.x - mousePosition.x, left.height }, MOUSE_CONTROL_AREA_RIGHT_COLOR);
    }
}
