#pragma once

#include <vector>

#include <raylib.h>

#include "util/Resource.h"

class Sprite : public Resource<Sprite>
{
public:
    const Texture& baseTexture;
    const Rectangle subArea;

    Sprite(const Texture& baseTexture, Rectangle subArea);
};