#include "MenuBackground.h"

#include "core/constants.h"
#include "core/Game.h"
#include "draw/draw.h"

void DrawMenuBackground()
{
    for (int i = 0; i < TILES_X; ++i)
        for (int j = 0; j < TILES_Y; ++j)
            DrawSpriteScreen(Sprite::get("spr_BaseTileBG"), i * BACKGROUND_TILE_DIMENSIONS, j * BACKGROUND_TILE_DIMENSIONS);

    DrawUIBox({ TILES_X / 2, TILES_Y / 2, TILES_X - 6, TILES_Y - 6 });
}

void DrawUIBox(Rectangle shape)
{
    for (int i = 1; i < shape.width - 1; ++i)
        for (int j = 1; j < shape.height - 1; ++j)
            DrawSpriteScreen(
                Sprite::get("spr_UIBoxCenter"),
                (shape.x + i - shape.width / 2) * TILE_DIMENSIONS,
                (shape.y + j - shape.height / 2) * TILE_DIMENSIONS);

    for (int i = 1; i < shape.height - 1; ++i)
    {
        DrawSpriteScreen(
            Sprite::get("spr_UIBoxLeft"),
            (shape.x - shape.width / 2) * TILE_DIMENSIONS,
            (shape.y + i - shape.height / 2) * TILE_DIMENSIONS);

        DrawSpriteScreen(
            Sprite::get("spr_UIBoxLeft"),
            (shape.x + shape.width / 2 - 1) * TILE_DIMENSIONS,
            (shape.y + i - shape.height / 2) * TILE_DIMENSIONS,
            true);
    }

    for (int i = 1; i < shape.width - 1; ++i)
    {
        DrawSpriteScreen(
            Sprite::get("spr_UIBoxTop"),
            (shape.x + i - shape.width / 2) * TILE_DIMENSIONS,
            (shape.y - shape.height / 2) * TILE_DIMENSIONS);

        DrawSpriteScreen(
            Sprite::get("spr_UIBoxBottom"),
            (shape.x + i - shape.width / 2) * TILE_DIMENSIONS,
            (shape.y + shape.height / 2 - 1) * TILE_DIMENSIONS);
    }

    DrawSpriteScreen(
        Sprite::get("spr_UIBoxTopLeft"),
        (shape.x - shape.width / 2) * TILE_DIMENSIONS,
        (shape.y - shape.height / 2) * TILE_DIMENSIONS);

    DrawSpriteScreen(
        Sprite::get("spr_UIBoxBottomLeft"),
        (shape.x - shape.width / 2) * TILE_DIMENSIONS,
        (shape.y + shape.height / 2 - 1) * TILE_DIMENSIONS);

    DrawSpriteScreen(
        Sprite::get("spr_UIBoxTopLeft"),
        (shape.x + shape.width / 2 - 1) * TILE_DIMENSIONS,
        (shape.y - shape.height / 2) * TILE_DIMENSIONS,
        true);

    DrawSpriteScreen(
        Sprite::get("spr_UIBoxBottomLeft"),
        (shape.x + shape.width / 2 - 1) * TILE_DIMENSIONS,
        (shape.y + shape.height / 2 - 1) * TILE_DIMENSIONS,
        true);
}
