#include "GameOver.h"

#include <raylib.h>

#include "core/constants.h""
#include "core/Game.h""
#include "draw/draw.h""
#include "MenuBackground.h""

void DrawGameOverScreen()
{
    DrawUIBox({ TILES_X / 2, TILES_Y / 2, TILES_X - 6, TILES_Y - 6 });

    DrawText(
        "Game Over",
        (LEVEL_WIDTH * ZOOM - MeasureText("Game Over", 10.0f * ZOOM)) * 0.5f,
        (LEVEL_HEIGHT * 0.25f - 5.0f) * ZOOM,
        10.0f * ZOOM,
        WHITE);

    DrawText(
        "Depth reached:",
        LEVEL_WIDTH * ZOOM * 0.25f,
        (LEVEL_HEIGHT * 0.5f - 2.5f) * ZOOM,
        5.0f * ZOOM,
        WHITE);
    DrawInt(
        Game::getPlayer().y,
        LEVEL_WIDTH * ZOOM * 0.75f,
        (LEVEL_HEIGHT * 0.5f - 3.5f) * ZOOM,
        7.0f * ZOOM,
        WHITE,
        TextAlignment::Right);

    DrawText(
        "Time survived:",
        LEVEL_WIDTH * ZOOM * 0.25f,
        (LEVEL_HEIGHT * 0.4f - 2.5f) * ZOOM,
        5.0f * ZOOM,
        WHITE);
    DrawInt(
        Game::getDeathTime() - Game::getSpawnTime(),
        LEVEL_WIDTH * ZOOM * 0.75f - MeasureText("s", 6.0f * ZOOM),
        (LEVEL_HEIGHT * 0.4f - 3.5f) * ZOOM,
        7.0f * ZOOM,
        WHITE,
        TextAlignment::Right);
    DrawText(
        "s",
        LEVEL_WIDTH * ZOOM * 0.75f - MeasureText("s", 5.0f * ZOOM),
        (LEVEL_HEIGHT * 0.4f - 2.5f) * ZOOM,
        5.0f * ZOOM,
        WHITE);
}
