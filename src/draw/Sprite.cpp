#include "Sprite.h"

Sprite& Animation::getCurrentSprite(float animTime)
{
    float acc = 0.0f;

    for (Frame& f : frames)
        if (animTime < (acc += f.duration))
            return f.sprite;

    return frames.back().sprite;
}

TextureInfo::TextureInfo(const char* filePath) : texture(LoadTexture(filePath)) {}
