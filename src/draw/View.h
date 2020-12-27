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

    void drawSprite(const Sprite& sprite, Vector2 position, bool mirror = false);
    void drawSprite(const Sprite& sprite, float x, float y, bool mirror = false);
    void drawSpriteScreen(const Sprite& sprite, float x, float y, bool mirror = false);
    void drawSpriteParallax(const Sprite& sprite, float x, float y, float zoom, bool mirror = false);
    void update();

    float getY();
};