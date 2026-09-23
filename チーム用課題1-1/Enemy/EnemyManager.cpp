#include "EnemyManager.h"
#include "../Field/Field.h"
#include <algorithm>

EnemyManager::EnemyManager(const EnemyDefinition& definition): definition_(definition), vision_(definition)
{
}

void EnemyManager::Spawn(const Vector2& position)
{
    enemies_.emplace_back(position, definition_);
}

void EnemyManager::Update(const Vector2& playerPosition,const Field& field,float deltaSeconds)
{
    updatedEnemyCount_ = 0;

    for (Enemy& enemy : enemies_)
    {
        if (enemy.IsDead() || enemy.IsRemovalRequested())
        {
            continue;
        }

        enemy.TickDecisionTimer(deltaSeconds);
        if (enemy.GetDecisionTimer() <= 0.0f)
        {
            UpdateDecision(enemy, playerPosition, field);
            enemy.ResetDecisionTimer();
        }

        if (Length(playerPosition - enemy.GetPosition()) > ActiveDistance)
        {
            continue;
        }

        UpdateMovement(enemy, playerPosition, deltaSeconds);
        ++updatedEnemyCount_;
    }
}

void EnemyManager::UpdateDecision(Enemy& enemy,const Vector2& playerPosition,const Field& field)
{
    if (vision_.CanSee(enemy, playerPosition, field))
    {
        enemy.SetLastKnownPlayerPosition(playerPosition);
        enemy.IncreaseAwareness(AwarenessGain);
    }
    else
    {
        enemy.DecreaseAwareness(AwarenessLoss);
    }

    if (enemy.GetAwareness() >= ChaseThreshold)
    {
        enemy.SetState(EnemyBehaviorState::Chase);
    }
    else if (enemy.GetAwareness() >= AlertThreshold)
    {
        enemy.SetState(EnemyBehaviorState::Alert);
    }
    else if (enemy.GetAwareness() >= SuspiciousThreshold)
    {
        enemy.SetState(EnemyBehaviorState::Suspicious);
    }
    else
    {
        enemy.SetState(EnemyBehaviorState::Patrol);
    }
}

void EnemyManager::UpdateMovement(Enemy& enemy,const Vector2& playerPosition,float deltaSeconds)
{
    switch (enemy.GetState())
    {
    case EnemyBehaviorState::Chase:
        enemy.MoveToward(playerPosition,definition_.chaseSpeed,deltaSeconds);
        break;

    case EnemyBehaviorState::Suspicious:
    case EnemyBehaviorState::Alert:
        enemy.MoveToward(enemy.GetLastKnownPlayerPosition(),definition_.patrolSpeed,deltaSeconds);
        break;

    case EnemyBehaviorState::Patrol:
        enemy.MoveToward(enemy.GetHomePosition(),definition_.patrolSpeed,deltaSeconds);
        break;

    default:
        break;
    }
}

void EnemyManager::CommitRemovals()
{
    std::erase_if(enemies_, [](const Enemy& enemy)
    {
        return enemy.IsRemovalRequested();
    });
}

std::vector<Enemy>& EnemyManager::GetEnemies() { return enemies_; }
const std::vector<Enemy>& EnemyManager::GetEnemies() const { return enemies_; }
int EnemyManager::GetUpdatedEnemyCount() const { return updatedEnemyCount_; }
