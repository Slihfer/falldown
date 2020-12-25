#include "Sprite.h"

void Animation::constructFrames()
{
    for (const Frame& f : frames)
        duration += f.duration;
}

//TODO make more efficient
const Sprite& Animation::getCurrentSprite(float animTime, bool loop) const
{
    if (loop)
        animTime = fmodf(animTime, duration);

    float acc = 0.0f;

    for (const Frame& f : frames)
        if (animTime < (acc += f.duration))
            return f.sprite;

    return frames.back().sprite;
}

TextureInfo::TextureInfo(const char* filePath) : texture(LoadTexture(filePath)) {}

TextureInfo::~TextureInfo()
{
    UnloadTexture(texture);
}

Sprite::Sprite(const Texture& baseTexture, Rectangle subArea) :
    baseTexture(baseTexture),
    subArea(subArea) {}
