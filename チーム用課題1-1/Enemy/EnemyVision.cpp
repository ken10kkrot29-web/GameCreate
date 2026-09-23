#include "EnemyVision.h"
#include "Enemy.h"
#include "../Field/Field.h"

EnemyVision::EnemyVision(const EnemyDefinition& definition): definition_(definition)
{
}

bool EnemyVision::CanSee(const Enemy& enemy,const Vector2& targetPosition,const Field& field) const
{
    const Vector2 toTarget = targetPosition - enemy.GetPosition();

    const float viewDistanceSquared =definition_.viewDistance * definition_.viewDistance;

    if (LengthSquared(toTarget) > viewDistanceSquared)
    {
        return false;
    }

    const Vector2 directionToTarget = Normalize(toTarget);
    const float facingDot = Dot(enemy.GetFacingDirection(),directionToTarget);

    if (facingDot < definition_.viewHalfAngleCosine)
    {
        return false;
    }

    return !field.IsSightBlocked(enemy.GetPosition(),targetPosition);
}
