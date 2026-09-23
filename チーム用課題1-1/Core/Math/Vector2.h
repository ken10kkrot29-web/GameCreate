#pragma once

#include <cmath>

struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;
};

inline Vector2 operator+(const Vector2& left, const Vector2& right)
{
    return { left.x + right.x, left.y + right.y };
}

inline Vector2 operator-(const Vector2& left, const Vector2& right)
{
    return { left.x - right.x, left.y - right.y };
}

inline Vector2 operator*(const Vector2& vector, float scalar)
{
    return { vector.x * scalar, vector.y * scalar };
}

inline float Dot(const Vector2& left, const Vector2& right)
{
    return left.x * right.x + left.y * right.y;
}

inline float LengthSquared(const Vector2& vector)
{
    return Dot(vector, vector);
}

inline float Length(const Vector2& vector)
{
    return std::sqrt(LengthSquared(vector));
}

inline Vector2 Normalize(const Vector2& vector)
{
    const float length = Length(vector);
    if (length <= 0.0001f)
    {
        return {};
    }

    return vector * (1.0f / length);
}
