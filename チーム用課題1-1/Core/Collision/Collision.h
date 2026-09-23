#pragma once

#include "../Math/Rect.h"

namespace Collision
{
    bool Intersects(const Rect& left, const Rect& right);
    bool IntersectsCircle(const Vector2& leftCenter,float leftRadius,const Vector2& rightCenter,float rightRadius);
    bool SegmentIntersectsRect(const Vector2& segmentStart,const Vector2& segmentEnd,const Rect& rect);
}
