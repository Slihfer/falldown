#pragma once

#include <raylib.h>

#include "util/Resource.h"

class TextureInfo : public Resource<TextureInfo>
{
public:
    const Texture texture;

    TextureInfo(const char* filePath);
    ~TextureInfo();
};