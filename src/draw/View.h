#pragma once

#include <raylib.h>

#include "Sprite.h"

class View
{
private:
    float y;

public:
    void drawSprite(Sprite& sprite, Vector2 position);
    void drawSprite(Sprite& sprite, float x, float y);
};