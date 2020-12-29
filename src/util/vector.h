#pragma once

#include <algorithm>
#include <iostream>

#include <raylib.h>

struct Vector2Int { int x, y; };

Vector2 operator-(Vector2 vector);

Vector2 operator+(Vector2 first, Vector2 second);
Vector2 operator-(Vector2 first, Vector2 second);
Vector2 operator*(Vector2 first, Vector2 second);
Vector2 operator/(Vector2 first, Vector2 second);
Vector2& operator+=(Vector2& first, Vector2 second);
Vector2& operator-=(Vector2& first, Vector2 second);
Vector2& operator*=(Vector2& first, Vector2 second);
Vector2& operator/=(Vector2& first, Vector2 second);

Vector2 operator+(Vector2 vector, float scalar);
Vector2 operator-(Vector2 vector, float scalar);
Vector2 operator*(Vector2 vector, float scalar);
Vector2 operator/(Vector2 vector, float scalar);
Vector2 operator+(float scalar, Vector2 vector);
Vector2 operator-(float scalar, Vector2 vector);
Vector2 operator*(float scalar, Vector2 vector);
Vector2 operator/(float scalar, Vector2 vector);
Vector2& operator+=(Vector2& vector, float scalar);
Vector2& operator-=(Vector2& vector, float scalar);
Vector2& operator*=(Vector2& vector, float scalar);
Vector2& operator/=(Vector2& vector, float scalar);

bool operator==(Vector2 first, Vector2 second);
bool operator!=(Vector2 first, Vector2 second);
bool operator<(Vector2 first, Vector2 second);
bool operator<=(Vector2 first, Vector2 second);
bool operator>(Vector2 first, Vector2 second);
bool operator>=(Vector2 first, Vector2 second);

float length(Vector2 vector);
float distance(Vector2 first, Vector2 second);
float dot(Vector2 first, Vector2 second);
Vector2 abs(Vector2 vector);
Vector2 min(Vector2 first, Vector2 second);
Vector2 max(Vector2 first, Vector2 second);
Vector2 floor(Vector2 vector);
Vector2 ceil(Vector2 vector);
Vector2 normalize(Vector2 vector);
Vector2 clamp(Vector2 value, Vector2 low, Vector2 high);
Vector2 round(Vector2 vector);

template <typename T>
T sign(T value)
{
    return (value > 0) - (value < 0);
}

template <>
inline Vector2 sign<Vector2>(Vector2 value)
{
    return { sign(value.x), sign(value.y) };
}

std::ostream& operator<<(std::ostream& os, Vector2 vector);