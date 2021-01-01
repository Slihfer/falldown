#include "Credits.h"

#include <raylib.h>

#include "core/constants.h"
#include "Level.h"

void DrawCreditsScreen()
{
    DrawText(
        "Credits",
        (LEVEL_WIDTH * ZOOM - MeasureText("Credits", 10.0f * ZOOM)) * 0.5f,
        (LEVEL_HEIGHT * 0.25f - 5.0f) * ZOOM,
        10.0f * ZOOM,
        WHITE);
    DrawText(
        "By",
        LEVEL_WIDTH * ZOOM * 0.25f,
        (LEVEL_HEIGHT * 0.4f - 2.5f) * ZOOM,
        5.0f * ZOOM,
        WHITE);
    DrawText(
        "Fritz Kraske",
        LEVEL_WIDTH * ZOOM * 0.75f - MeasureText("Fritz Kraske", 7.0f * ZOOM),
        (LEVEL_HEIGHT * 0.4f - 3.5f) * ZOOM,
        7.0f * ZOOM,
        WHITE);
    DrawText(
        "Made with",
        LEVEL_WIDTH * ZOOM * 0.3f,
        (LEVEL_HEIGHT * 0.6f - 2.0f) * ZOOM,
        4.0f * ZOOM,
        WHITE);
    DrawText(
        "raylib",
        LEVEL_WIDTH * ZOOM * 0.7f - MeasureText("raylib", 5.0f * ZOOM),
        (LEVEL_HEIGHT * 0.6f + 5.0f) * ZOOM,
        5.0f * ZOOM,
        WHITE);

    DrawRectangleLinesEx({
            (LEVEL_WIDTH * 0.7f - 22.0f) * ZOOM,
            (LEVEL_HEIGHT * 0.6f - 12.5f) * ZOOM,
            25.0f * ZOOM,
            25.0f * ZOOM},
        ZOOM,
        WHITE);
}
