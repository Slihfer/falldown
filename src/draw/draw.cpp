#include "draw.h"

#include <sstream>

#include "core/Game.h"

void DrawSpriteWorld(const Sprite& sprite, Vector2 position, bool mirror, BlendMode blendMode)
{
    DrawSpriteWorld(sprite, position.x, position.y, mirror, blendMode);
}

void DrawSpriteWorld(const Sprite& sprite, float x, float y, bool mirror, BlendMode blendMode)
{
    DrawSpriteScreen(sprite, x, y - Game::getView().getY(), mirror, blendMode);
}

void DrawSpriteParallax(const Sprite& sprite, float x, float y, float zoom, bool mirror, BlendMode blendMode)
{
    DrawSpriteScreen(sprite, zoom * x, zoom * (y - Game::getView().getY()), mirror, blendMode);
}

void DrawSpriteScreen(const Sprite& sprite, float x, float y, bool mirror, BlendMode blendMode)
{
    if (blendMode != BLEND_ALPHA)
        BeginBlendMode(BLEND_ADDITIVE);

    DrawTexturePro(
        sprite.baseTexture,
        { floor(sprite.subArea.x), floor(sprite.subArea.y), mirror ? -sprite.subArea.width : sprite.subArea.width, sprite.subArea.height },
        { floor(ZOOM * x), floor(ZOOM * y), ZOOM * sprite.subArea.width, ZOOM * sprite.subArea.height },
        {},
        0,
        WHITE);

    if (blendMode != BLEND_ALPHA)
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
