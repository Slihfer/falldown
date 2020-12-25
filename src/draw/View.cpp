#include "View.h"

#include "core/constants.h"

View::View() : y(0), scrollSpeed(2) {}

void View::drawSprite(const Sprite& sprite, Vector2 position)
{
    drawSprite(sprite, position.x, position.y);
}

void View::drawSprite(const Sprite& sprite, int x, int y)
{
    DrawTexturePro(
        sprite.baseTexture,
        { floor(sprite.subArea.x), floor(sprite.subArea.y), sprite.mirror ? -sprite.subArea.width : sprite.subArea.width, sprite.subArea.height },
        { static_cast<float>(x), static_cast<float>(y) - floor(this->y), sprite.subArea.width, sprite.subArea.height },
        {},
        0,
        WHITE);
}

void View::update(float t)
{
    y += t * scrollSpeed * TILE_DIMENSIONS;
}

float View::getY()
{
    return y;
}
