#pragma once

#include <vector>

#include <raylib.h>

#include "util/Resource.h"

class Sprite : public Resource<Sprite>
{
public:
    const Texture& baseTexture;
    const Rectangle subArea;
    bool mirror;

    Sprite(const Texture& baseTexture, Rectangle subArea, bool mirror);
};

class TextureInfo : public Resource<TextureInfo>
{
public:
    const Texture texture;

    TextureInfo(const char* filePath);
    ~TextureInfo();
};

class Animation : public Resource<Animation>
{
public:
    struct Frame
    {
        Sprite sprite;
        float duration;
    };

private:
    std::vector<Frame> frames;

public:
    template <class ... TArgs>
    Animation(Frame frame, TArgs ... args) : Animation(args ...)
    {
        frames.push_back(frame);
    }

    Animation() {}

    Sprite& getCurrentSprite(float animTime);
};