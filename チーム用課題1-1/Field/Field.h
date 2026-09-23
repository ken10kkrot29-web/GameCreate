#pragma once

#include "../Core/Math/Rect.h"

class Field
{
public:
    Field();

    Vector2 ConstrainPosition(const Vector2& position, float radius) const;
    bool CollidesWithSolidObject(const Rect& bounds) const;
    bool IsSightBlocked(const Vector2& from, const Vector2& to) const;

    void DestroyBreakableWall();

    const Rect& GetBreakableWallBounds() const;
    const Rect& GetMissionTargetBounds() const;
    const Rect& GetExtractionBounds() const;
    float GetWidth() const;
    float GetHeight() const;
    bool IsBreakableWallDestroyed() const;

private:
    static constexpr float Width = 1600.0f;
    static constexpr float Height = 900.0f;

    Rect breakableWallBounds_ = { 700.0f, 250.0f, 45.0f, 300.0f };
    Rect missionTargetBounds_ = { 1320.0f, 285.0f, 90.0f, 150.0f };
    Rect extractionBounds_ = { 1460.0f, 700.0f, 100.0f, 100.0f };
    bool breakableWallDestroyed_ = false;
};
