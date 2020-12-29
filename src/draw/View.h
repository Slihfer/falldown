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

    void update();

    float getY();

public:
    static constexpr float MIN_SCROLL_SPEED = 2;
    static constexpr float MAX_SCROLL_SPEED = 8;
    static constexpr float SCROLL_ACCELERATION = 0.05f;
};