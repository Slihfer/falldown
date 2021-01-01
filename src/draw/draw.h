#pragma once

#include <raylib.h>

#include "Sprite.h"
#include "View.h"

enum class TextAlignment
{
    Left,
    Center,
    Right
};

void DrawSpriteWorld(const Sprite& sprite, Vector2 position, bool mirror = false, BlendMode blendMode = BLEND_ALPHA);
void DrawSpriteWorld(const Sprite& sprite, float x, float y, bool mirror = false, BlendMode blendMode = BLEND_ALPHA);
void DrawSpriteParallax(const Sprite& sprite, float x, float y, float zoom, bool mirror = false, BlendMode blendMode = BLEND_ALPHA);
void DrawSpriteScreen(const Sprite& sprite, float x, float y, bool mirror = false, BlendMode blendMode = BLEND_ALPHA);

void DrawInt(int value, int x, int y, int fontSize = 5, Color color = WHITE, TextAlignment align = TextAlignment::Center);
void DrawFloat(float value, int x, int y, int fontSize = 5, Color color = WHITE, TextAlignment align = TextAlignment::Center);