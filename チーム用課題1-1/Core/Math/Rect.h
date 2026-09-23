#pragma once

#include "Vector2.h"

struct Rect
{
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
};

inline Vector2 Center(const Rect& rect)
{
    return {rect.x + rect.width * 0.5f,rect.y + rect.height * 0.5f};
}
