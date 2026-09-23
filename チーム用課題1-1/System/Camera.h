#pragma once

#include "../Core/Math/Vector2.h"

class Camera
{
public:
    void Follow(const Vector2& targetPosition,float fieldWidth,float fieldHeight);

    Vector2 WorldToScreen(const Vector2& worldPosition) const;
    Vector2 GetPosition() const;

private:
    Vector2 position_;
};
