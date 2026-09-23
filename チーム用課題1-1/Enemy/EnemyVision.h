#pragma once

#include "EnemyDefinition.h"
#include "../Core/Math/Vector2.h"

class Enemy;
class Field;

class EnemyVision
{
public:
    explicit EnemyVision(const EnemyDefinition& definition);

    bool CanSee(const Enemy& enemy,const Vector2& targetPosition,const Field& field) const;

private:
    EnemyDefinition definition_;
};
