#include "draw.h"

#include <sstream>

#include "core/Game.h"

void DrawSpriteWorld(const Sprite& sprite, Vector2 position, bool mirror, bool additive)
{
    DrawSpriteWorld(sprite, position.x, position.y, mirror, additive);
}

void DrawSpriteWorld(const Sprite& sprite, float x, float y, bool mirror, bool additive)
{
    DrawSpriteScreen(sprite, x, y - Game::getView().getY(), mirror, additive);
}

void DrawSpriteParallax(const Sprite& sprite, float x, float y, float zoom, bool mirror, bool additive)
{
    DrawSpriteScreen(sprite, zoom * x, zoom * (y - Game::getView().getY()), mirror, additive);
}

void DrawSpriteScreen(const Sprite& sprite, float x, float y, bool mirror, bool additive)
{
    if (additive)
        BeginBlendMode(BLEND_ADDITIVE);

    DrawTexturePro(
        sprite.baseTexture,
        { floor(sprite.subArea.x), floor(sprite.subArea.y), mirror ? -sprite.subArea.width : sprite.subArea.width, sprite.subArea.height },
        { floor(ZOOM * x), floor(ZOOM * y), ZOOM * sprite.subArea.width, ZOOM * sprite.subArea.height },
        {},
        0,
        WHITE);

    if (additive)
        EndBlendMode();
}

void DrawInt(int value, int x, int y, int size, Color color)
{
    std::ostringstream stream;
    stream << value;
    DrawText(stream.str().c_str(), x, y, size, color);
}

void DrawFloat(float value, int x, int y, int size, Color color)
{
    std::ostringstream stream;
    stream << value;
    DrawText(stream.str().c_str(), x, y, size, color);
}
