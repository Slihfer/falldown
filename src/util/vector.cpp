#include "vector.h"

#include <cmath>
#include <algorithm>

Vector2 operator-(Vector2 vector)
{
    return { -vector.x, -vector.y };
}

Vector2 operator+(Vector2 first, Vector2 second)
{
    return { first.x + second.x, first.y + second.y };
}

Vector2 operator-(Vector2 first, Vector2 second)
{
    return { first.x - second.x, first.y - second.y };
}

Vector2 operator*(Vector2 first, Vector2 second)
{
    return { first.x * second.x, first.y * second.y };
}

Vector2 operator/(Vector2 first, Vector2 second)
{
    return { first.x / second.x, first.y / second.y };
}

Vector2& operator+=(Vector2& first, Vector2 second)
{
    first.x += second.x;
    first.y += second.y;

    return first;
}

Vector2& operator-=(Vector2& first, Vector2 second)
{
    first.x -= second.x;
    first.y -= second.y;

    return first;
}

Vector2& operator*=(Vector2& first, Vector2 second)
{
    first.x *= second.x;
    first.y *= second.y;

    return first;
}

Vector2& operator/=(Vector2& first, Vector2 second)
{
    first.x /= second.x;
    first.y /= second.y;

    return first;
}

Vector2 operator+(Vector2 vector, float scalar)
{
    return { vector.x + scalar, vector.y + scalar };
}

Vector2 operator-(Vector2 vector, float scalar)
{
    return { vector.x - scalar, vector.y - scalar };
}

Vector2 operator*(Vector2 vector, float scalar)
{
    return { vector.x * scalar, vector.y * scalar };
}

Vector2 operator/(Vector2 vector, float scalar)
{
    return { vector.x / scalar, vector.y / scalar };
}

Vector2 operator+(float scalar, Vector2 vector)
{
    return vector + scalar;
}

Vector2 operator-(float scalar, Vector2 vector)
{
    return -vector + scalar;
}

Vector2 operator*(float scalar, Vector2 vector)
{
    return vector * scalar;
}

Vector2 operator/(float scalar, Vector2 vector)
{
    return vector / scalar;
}

Vector2& operator+=(Vector2& vector, float scalar)
{
    vector.x += scalar;
    vector.y += scalar;

    return vector;
}

Vector2& operator-=(Vector2& vector, float scalar)
{
    vector.x -= scalar;
    vector.y -= scalar;

    return vector;
}

Vector2& operator*=(Vector2& vector, float scalar)
{
    vector.x *= scalar;
    vector.y *= scalar;

    return vector;
}

Vector2& operator/=(Vector2& vector, float scalar)
{
    vector.x /= scalar;
    vector.y /= scalar;

    return vector;
}

bool operator==(Vector2 first, Vector2 second)
{
    return first.x == second.x && first.y == second.y;
}

bool operator!=(Vector2 first, Vector2 second)
{
    return first.x != second.x || first.y != second.y;
}

bool operator<(Vector2 first, Vector2 second)
{
    return first.x < second.x && first.y < second.y;
}

bool operator<=(Vector2 first, Vector2 second)
{
    return first.x <= second.x && first.y <= second.y;
}

bool operator>(Vector2 first, Vector2 second)
{
    return first.x > second.x && first.y > second.y;
}

bool operator>=(Vector2 first, Vector2 second)
{
    return first.x >= second.x && first.y >= second.y;
}

float length(Vector2 vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float distance(Vector2 first, Vector2 second)
{
    return length(first - second);
}

float dot(Vector2 first, Vector2 second)
{
    return first.x * second.x + first.y * second.y;
}

Vector2 abs(Vector2 vector)
{
    return { fabsf(vector.x), fabsf(vector.y) };
}

Vector2 min(Vector2 first, Vector2 second)
{
    return { std::min(first.x, second.x), std::min(first.y, second.y) };
}

Vector2 max(Vector2 first, Vector2 second)
{
    return { std::max(first.x, second.x), std::max(first.y, second.y) };
}

Vector2 floor(Vector2 vector)
{
    return { floor(vector.x), floor(vector.y) };
}

Vector2 ceil(Vector2 vector)
{
    return { ceil(vector.x), ceil(vector.y) };
}

Vector2 normalize(Vector2 vector)
{
    float l = length(vector);

    if (l) return vector / l;

    return {};
}

Vector2 clamp(Vector2 value, Vector2 low, Vector2 high)
{
    return { std::clamp(value.x, low.x, high.x), std::clamp(value.y, low.y, high.y) };
}

Vector2 round(Vector2 vector)
{
    return { round(vector.x), round(vector.y) };
}

std::ostream& operator<<(std::ostream& os, Vector2 vector)
{
    return os << "(" << vector.x << ", " << vector.y << ")";
}