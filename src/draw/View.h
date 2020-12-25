#pragma once

#include <raylib.h>

#include "Sprite.h"

class View
{
private:
    float y;
    float scrollSpeed;

public:
    View();

    void drawSprite(const Sprite& sprite, Vector2 position);
    void drawSprite(const Sprite& sprite, float x, float y);
    void drawSpriteParallax(const Sprite& sprite, float x, float y, float zoom);
    void update(float t);

    float getY();
};