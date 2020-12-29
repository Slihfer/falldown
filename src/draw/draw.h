#pragma once

#include <raylib.h>

#include "Sprite.h"
#include "View.h"

void DrawSpriteWorld(const Sprite& sprite, Vector2 position, bool mirror = false, bool additive = false);
void DrawSpriteWorld(const Sprite& sprite, float x, float y, bool mirror = false, bool additive = false);
void DrawSpriteParallax(const Sprite& sprite, float x, float y, float zoom, bool mirror = false, bool additive = false);
void DrawSpriteScreen(const Sprite& sprite, float x, float y, bool mirror = false, bool additive = false);

void DrawInt(int value, int x, int y, int size = 20, Color color = WHITE);
void DrawFloat(float value, int x, int y, int size = 20, Color color = WHITE);