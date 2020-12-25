#include "View.h"

#include "core/constants.h"

View::View() : y(0), scrollSpeed(2) {}

void View::drawSprite(const Sprite& sprite, Vector2 position)
{
    drawSprite(sprite, position.x, position.y);
}

void View::drawSprite(const Sprite& sprite, float x, float y)
{
    DrawTexture(sprite.baseTexture, x, y - this->y, WHITE);
}

void View::update(float t)
{
    y += t * scrollSpeed * TILE_DIMENSIONS;
}

float View::getY()
{
    return y;
}
