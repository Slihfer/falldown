#include "Sprite.h"

Sprite::Sprite(const Texture& baseTexture, Rectangle subArea) :
    baseTexture(baseTexture),
    subArea(subArea) {}
