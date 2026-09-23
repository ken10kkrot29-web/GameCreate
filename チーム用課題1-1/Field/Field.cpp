#include "Field.h"
#include "../Core/Collision/Collision.h"
#include <algorithm>

Field::Field() = default;

Vector2 Field::ConstrainPosition(const Vector2& position,float radius) const
{
    return {std::clamp(position.x, radius, Width - radius),std::clamp(position.y, radius, Height - radius)};
}

bool Field::CollidesWithSolidObject(const Rect& bounds) const
{
    if (!breakableWallDestroyed_
        && Collision::Intersects(bounds, breakableWallBounds_))
    {
        return true;
    }

    return false;
}

bool Field::IsSightBlocked(const Vector2& from,const Vector2& to) const
{
    if (breakableWallDestroyed_)
    {
        return false;
    }

    return Collision::SegmentIntersectsRect(from,to,breakableWallBounds_);
}

void Field::DestroyBreakableWall()
{
    breakableWallDestroyed_ = true;
}

const Rect& Field::GetBreakableWallBounds() const { return breakableWallBounds_; }
const Rect& Field::GetMissionTargetBounds() const { return missionTargetBounds_; }
const Rect& Field::GetExtractionBounds() const { return extractionBounds_; }
float Field::GetWidth() const { return Width; }
float Field::GetHeight() const { return Height; }
bool Field::IsBreakableWallDestroyed() const { return breakableWallDestroyed_; }
