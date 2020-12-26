#include "TextureInfo.h"

TextureInfo::TextureInfo(const char* filePath) : texture(LoadTexture(filePath)) {}

TextureInfo::~TextureInfo()
{
    UnloadTexture(texture);
}