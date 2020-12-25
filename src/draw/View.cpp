#include "View.h"

#include "core/Game.h"
#include "core/constants.h"

View::View() : y(0), scrollSpeed(2) {}

void View::drawSprite(const Sprite& sprite, Vector2 position)
{
    drawSprite(sprite, position.x, position.y);
}

void View::drawSprite(const Sprite& sprite, float x, float y)
{
    DrawTexturePro(
        sprite.baseTexture,
        { floor(sprite.subArea.x), floor(sprite.subArea.y), sprite.mirror ? -sprite.subArea.width : sprite.subArea.width, sprite.subArea.height },
        { floor(ZOOM * x), floor(ZOOM * (y - this->y)), ZOOM * sprite.subArea.width, ZOOM * sprite.subArea.height },
        {},
        0,
        WHITE);
}

void View::drawSpriteParallax(const Sprite& sprite, float x, float y, float zoom)
{
    DrawTexturePro(
        sprite.baseTexture,
        { floor(sprite.subArea.x), floor(sprite.subArea.y), sprite.mirror ? -sprite.subArea.width : sprite.subArea.width, sprite.subArea.height },
        { floor(zoom * ZOOM * x), floor(zoom * ZOOM * (y - this->y)), ZOOM * sprite.subArea.width, ZOOM * sprite.subArea.height },
        {},
        0,
        WHITE);
}

void View::update(float t)
{
    y = std::max(y + t * scrollSpeed * TILE_DIMENSIONS, Game::getPlayer().y - VIEW_MAX_PLAYER_DISTANCE);
}

float View::getY()
{
    return y;
}
