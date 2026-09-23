#include "Enemy.h"

#include <algorithm>

Enemy::Enemy(Vector2 spawnPosition, const EnemyDefinition& definition)
    : definition_(definition)
    , position_(spawnPosition)
    , homePosition_(spawnPosition)
    , lastKnownPlayerPosition_(spawnPosition)
    , hp_(definition.maximumHp)
{
}

void Enemy::MoveToward(const Vector2& targetPosition,float speed,float deltaSeconds)
{
    const Vector2 direction = Normalize(targetPosition - position_);
    if (LengthSquared(direction) <= 0.0f)
    {
        return;
    }

    facingDirection_ = direction;
    position_ = position_ + direction * (speed * deltaSeconds);
}

void Enemy::ApplyDamage(int damage)
{
    if (state_ == EnemyBehaviorState::Dead)
    {
        return;
    }

    hp_ = (std::max)(0, hp_ - damage);
    state_ = hp_ == 0? EnemyBehaviorState::Dead: EnemyBehaviorState::Damage;
}

void Enemy::IncreaseAwareness(float amount)
{
    awareness_ = std::clamp(awareness_ + amount, 0.0f, 1.0f);
}

void Enemy::DecreaseAwareness(float amount)
{
    awareness_ = std::clamp(awareness_ - amount, 0.0f, 1.0f);
}

void Enemy::RequestRemoval() { removalRequested_ = true; }
Vector2 Enemy::GetPosition() const { return position_; }
Vector2 Enemy::GetHomePosition() const { return homePosition_; }
Vector2 Enemy::GetFacingDirection() const { return facingDirection_; }
Vector2 Enemy::GetLastKnownPlayerPosition() const { return lastKnownPlayerPosition_; }
float Enemy::GetCollisionRadius() const { return definition_.collisionRadius; }
float Enemy::GetAwareness() const { return awareness_; }
float Enemy::GetDecisionTimer() const { return decisionTimer_; }
EnemyBehaviorState Enemy::GetState() const { return state_; }
bool Enemy::IsDead() const { return state_ == EnemyBehaviorState::Dead; }
bool Enemy::IsRemovalRequested() const { return removalRequested_; }
void Enemy::SetState(EnemyBehaviorState state) { state_ = state; }
void Enemy::SetLastKnownPlayerPosition(const Vector2& position) { lastKnownPlayerPosition_ = position; }
void Enemy::ResetDecisionTimer() { decisionTimer_ = definition_.decisionIntervalSeconds; }
void Enemy::TickDecisionTimer(float deltaSeconds) { decisionTimer_ -= deltaSeconds; }
