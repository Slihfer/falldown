#include "MenuBackground.h"

#include "core/constants.h"
#include "core/Game.h"
#include "draw/draw.h"

void DrawMenuBackground()
{
    for (int i = 0; i < TILES_X; ++i)
        for (int j = 0; j < TILES_Y; ++j)
            DrawSpriteScreen(Sprite::get("spr_BaseTileBG"), i * BACKGROUND_TILE_DIMENSIONS, j * BACKGROUND_TILE_DIMENSIONS);
}