#pragma once

#include "../Core/Math/Vector2.h"
#include "EnemyDefinition.h"

enum class EnemyBehaviorState
{
    Patrol,
    Suspicious,
    Alert,
    Chase,
    Attack,
    Damage,
    Dead
};

class Enemy
{
public:
    Enemy(Vector2 spawnPosition, const EnemyDefinition& definition);

    void MoveToward(const Vector2& targetPosition, float speed, float deltaSeconds);
    void ApplyDamage(int damage);
    void IncreaseAwareness(float amount);
    void DecreaseAwareness(float amount);
    void RequestRemoval();

    Vector2 GetPosition() const;
    Vector2 GetHomePosition() const;
    Vector2 GetFacingDirection() const;
    Vector2 GetLastKnownPlayerPosition() const;
    float GetCollisionRadius() const;
    float GetAwareness() const;
    float GetDecisionTimer() const;
    EnemyBehaviorState GetState() const;
    bool IsDead() const;
    bool IsRemovalRequested() const;

    void SetState(EnemyBehaviorState state);
    void SetLastKnownPlayerPosition(const Vector2& position);
    void ResetDecisionTimer();
    void TickDecisionTimer(float deltaSeconds);

private:
    EnemyDefinition definition_;
    Vector2 position_;
    Vector2 homePosition_;
    Vector2 facingDirection_ = { 1.0f, 0.0f };
    Vector2 lastKnownPlayerPosition_;
    int hp_ = 0;
    float awareness_ = 0.0f;
    float decisionTimer_ = 0.0f;
    EnemyBehaviorState state_ = EnemyBehaviorState::Patrol;
    bool removalRequested_ = false;
};
