#include "View.h"

void View::drawSprite(Sprite& sprite, Vector2 position)
{
    drawSprite(sprite, position.x, position.y);
}

void View::drawSprite(Sprite& sprite, float x, float y)
{
    DrawTexture(sprite.baseTexture, x - sprite.baseTexture.width / 2, (y - sprite.baseTexture.height / 2) - this->y, WHITE);
}
