#include "Camera.h"
#include "../Config/GameConfig.h"
#include <algorithm>

void Camera::Follow(const Vector2& targetPosition,float fieldWidth,float fieldHeight)
{
    const float desiredX = targetPosition.x - GameConfig::ScreenWidth * 0.5f;
    const float desiredY = targetPosition.y - GameConfig::ScreenHeight * 0.5f;

    position_.x = std::clamp(desiredX,0.0f,fieldWidth - GameConfig::ScreenWidth);
    position_.y = std::clamp(desiredY,0.0f,fieldHeight - GameConfig::ScreenHeight);
}

Vector2 Camera::WorldToScreen(const Vector2& worldPosition) const
{
    return worldPosition - position_;
}

Vector2 Camera::GetPosition() const
{
    return position_;
}
