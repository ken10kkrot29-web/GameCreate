#pragma once

struct EnemyDefinition
{
    int maximumHp = 2;
    float patrolSpeed = 70.0f;
    float chaseSpeed = 105.0f;
    float collisionRadius = 16.0f;
    float viewDistance = 280.0f;
    float viewHalfAngleCosine = 0.7071067f;
    float decisionIntervalSeconds = 0.25f;
};
