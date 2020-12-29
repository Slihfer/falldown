#pragma once

#include <raylib.h>

Rectangle AssembleCollider(Vector2 position, Rectangle collider);
Vector2 GetFixedMobileUnstuckVector(Rectangle fixedCollider, Rectangle mobileCollider, Rectangle previousMobileCollider);