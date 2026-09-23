#pragma once

#include "Enemy.h"
#include "EnemyVision.h"
#include <vector>

class Field;

class EnemyManager
{
public:
    explicit EnemyManager(const EnemyDefinition& definition);

    void Spawn(const Vector2& position);
    void Update(const Vector2& playerPosition,const Field& field,float deltaSeconds);
    void CommitRemovals();

    std::vector<Enemy>& GetEnemies();
    const std::vector<Enemy>& GetEnemies() const;
    int GetUpdatedEnemyCount() const;

private:
    void UpdateDecision(Enemy& enemy, const Vector2& playerPosition, const Field& field);
    void UpdateMovement(Enemy& enemy, const Vector2& playerPosition, float deltaSeconds);

    static constexpr float AwarenessGain = 0.45f;
    static constexpr float AwarenessLoss = 0.20f;
    static constexpr float SuspiciousThreshold = 0.05f;
    static constexpr float AlertThreshold = 0.40f;
    static constexpr float ChaseThreshold = 0.75f;
    static constexpr float ActiveDistance = 520.0f;

    EnemyDefinition definition_;
    EnemyVision vision_;
    std::vector<Enemy> enemies_;
    int updatedEnemyCount_ = 0;
};
