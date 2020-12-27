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
};