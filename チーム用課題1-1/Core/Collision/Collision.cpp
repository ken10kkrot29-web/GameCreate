#include "Collision.h"
#include <algorithm>
#include <cmath>

bool Collision::Intersects(const Rect& left, const Rect& right)
{
    return left.x < right.x + right.width&& left.x + left.width > right.x&& left.y < right.y + right.height&& left.y + left.height > right.y;
}

bool Collision::IntersectsCircle(const Vector2& leftCenter,float leftRadius,const Vector2& rightCenter,float rightRadius)
{
    const float combinedRadius = leftRadius + rightRadius;
    return LengthSquared(leftCenter - rightCenter)<= combinedRadius * combinedRadius;
}

bool Collision::SegmentIntersectsRect(const Vector2& segmentStart,const Vector2& segmentEnd,const Rect& rect)
{
    const Vector2 direction = segmentEnd - segmentStart;
    float entryTime = 0.0f;
    float exitTime = 1.0f;

    const auto clipAxis = [&entryTime, &exitTime](float start,float directionValue,float minimum,float maximum)
    {
        if (std::fabs(directionValue) <= 0.0001f)
        {
            return start >= minimum && start <= maximum;
        }

        float firstTime = (minimum - start) / directionValue;
        float secondTime = (maximum - start) / directionValue;

        if (firstTime > secondTime)
        {
            std::swap(firstTime, secondTime);
        }

        entryTime = (std::max)(entryTime, firstTime);
        exitTime = (std::min)(exitTime, secondTime);
        return entryTime <= exitTime;
    };

    const bool intersectsX = clipAxis(segmentStart.x,direction.x,rect.x, rect.x + rect.width);

    if (!intersectsX)
    {
        return false;
    }

    return clipAxis(segmentStart.y,direction.y,rect.y,rect.y + rect.height);
}
