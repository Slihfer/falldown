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

    for (int i = 0; i <= TILES_Y; ++i)
    {
        DrawRectangle(left.x + left.width - ZOOM, (i - 0.25f) * ZOOMED_TILE_DIMENSIONS, ZOOM, ZOOMED_HALF_TILE_DIMENSIONS, MOUSE_CONTROL_SEPARATOR);
        DrawRectangle(right.x, (i - 0.25f) * ZOOMED_TILE_DIMENSIONS, ZOOM, ZOOMED_HALF_TILE_DIMENSIONS, MOUSE_CONTROL_SEPARATOR);
    }

    if (highlightLeft)
        DrawRectangleRec(left, MOUSE_CONTROL_AREA_HIGHLIGHT);
    else if (highlightRight)
        DrawRectangleRec(right, MOUSE_CONTROL_AREA_HIGHLIGHT);
#if MOUSE_INDICATOR
    else
    {
        float startY = (ceil(Game::getMousePosition().y / ZOOMED_TILE_DIMENSIONS - 1.5f) - 0.25f) * ZOOMED_TILE_DIMENSIONS;

        for (float y = startY; y < startY + 2.5f * ZOOMED_TILE_DIMENSIONS; y += ZOOMED_TILE_DIMENSIONS)
            DrawRectangle(
                Game::getMousePosition().x - 0.5f * ZOOM,
                y,
                ZOOM,
                ZOOMED_HALF_TILE_DIMENSIONS,
                {
                    MOUSE_CONTROL_SEPARATOR.r,
                    MOUSE_CONTROL_SEPARATOR.g,
                    MOUSE_CONTROL_SEPARATOR.b,
                    static_cast<unsigned char>(MOUSE_CONTROL_SEPARATOR.a * (1 - std::min(1.0f, abs(y + 0.5f * ZOOMED_HALF_TILE_DIMENSIONS - Game::getMousePosition().y) / 1.5f / ZOOMED_TILE_DIMENSIONS)))
                });

        float startX = (ceil(Game::getMousePosition().x / ZOOMED_TILE_DIMENSIONS - 1.5f) - 0.25f) * ZOOMED_TILE_DIMENSIONS;

        for (float x = startX; x < startX + 2.5f * ZOOMED_TILE_DIMENSIONS; x += ZOOMED_TILE_DIMENSIONS)
            DrawRectangle(
                std::max(x, left.x + left.width),
                Game::getMousePosition().y - ZOOM * 0.5f,
                std::min(std::min(static_cast<float>(ZOOMED_HALF_TILE_DIMENSIONS), right.x - x), x + ZOOMED_HALF_TILE_DIMENSIONS - left.x - left.width),
                ZOOM,
                {
                    MOUSE_CONTROL_SEPARATOR.r,
                    MOUSE_CONTROL_SEPARATOR.g,
                    MOUSE_CONTROL_SEPARATOR.b,
                    static_cast<unsigned char>(MOUSE_CONTROL_SEPARATOR.a * (1 - std::min(1.0f, abs(x + 0.5f * ZOOMED_HALF_TILE_DIMENSIONS - Game::getMousePosition().x) / 1.5f / ZOOMED_TILE_DIMENSIONS)))
                });
    }
#endif
}
