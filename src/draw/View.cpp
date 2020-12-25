#include "View.h"

#include "core/Game.h"
#include "core/constants.h"

View::View() : y(0), scrollSpeed(2) {}

void View::drawSprite(const Sprite& sprite, Vector2 position, bool mirror)
{
    drawSprite(sprite, position.x, position.y, mirror);
}

void View::drawSprite(const Sprite& sprite, float x, float y, bool mirror)
{
    DrawTexturePro(
        sprite.baseTexture,
        { floor(sprite.subArea.x), floor(sprite.subArea.y), mirror ? -sprite.subArea.width : sprite.subArea.width, sprite.subArea.height },
        { floor(ZOOM * x), floor(ZOOM * (y - this->y)), ZOOM * sprite.subArea.width, ZOOM * sprite.subArea.height },
        {},
        0,
        WHITE);
}

void View::drawSpriteParallax(const Sprite& sprite, float x, float y, float zoom, bool mirror)
{
    DrawTexturePro(
        sprite.baseTexture,
        { floor(sprite.subArea.x), floor(sprite.subArea.y), mirror ? -sprite.subArea.width : sprite.subArea.width, sprite.subArea.height },
        { floor(zoom * ZOOM * x), floor(zoom * ZOOM * (y - this->y)), ZOOM * sprite.subArea.width, ZOOM * sprite.subArea.height },
        {},
        0,
        WHITE);
}

void View::update()
{
    y = std::max(y + Game::delta() * scrollSpeed * TILE_DIMENSIONS, Game::getPlayer().y - VIEW_MAX_PLAYER_DISTANCE);
}

float View::getY()
{
    return y;
}
