#include "CollisionSystem.h"
#include "../Core/Collision/Collision.h"
#include "../Enemy/EnemyManager.h"
#include "../Item/ItemManager.h"
#include "../Player/Player.h"

std::vector<EnemyHitEvent> CollisionSystem::FindKnifeHits(const Player& player,const EnemyManager& enemyManager) const
{
    std::vector<EnemyHitEvent> events;
    lastCandidateCount_ = 0;

    if (!player.IsAttackActive())
    {
        return events;
    }

    const std::vector<Enemy>& enemies = enemyManager.GetEnemies();
    for (std::size_t index = 0; index < enemies.size(); ++index)
    {
        const Enemy& enemy = enemies[index];
        if (enemy.IsDead() || enemy.IsRemovalRequested())
        {
            continue;
        }

        ++lastCandidateCount_;
        if (Collision::IntersectsCircle(player.GetAttackCenter(),player.GetAttackRadius(),enemy.GetPosition(),enemy.GetCollisionRadius()))
        {
            events.push_back({ index, KnifeDamage });
        }
    }
    return events;
}

std::vector<ItemPickupEvent> CollisionSystem::FindItemPickups(const Player& player,const ItemManager& itemManager) const
{
    constexpr float PickupRadius = 18.0f;
    constexpr float WorldItemRadius = 12.0f;

    std::vector<ItemPickupEvent> events;
    const std::vector<WorldItem>& items = itemManager.GetItems();

    for (std::size_t index = 0; index < items.size(); ++index)
    {
        if (items[index].removalRequested)
        {
            continue;
        }

        if (Collision::IntersectsCircle(player.GetPosition(),PickupRadius,items[index].position,WorldItemRadius))
        {
            events.push_back({ index });
        }
    }
    return events;
}

bool CollisionSystem::IsPlayerTouchingEnemy(const Player& player,const EnemyManager& enemyManager) const
{
    constexpr float PlayerRadius = 14.0f;

    for (const Enemy& enemy : enemyManager.GetEnemies())
    {
        if (!enemy.IsDead()&& Collision::IntersectsCircle(player.GetPosition(),PlayerRadius,enemy.GetPosition(),enemy.GetCollisionRadius()))
        {
            return true;
        }
    }
    return false;
}

int CollisionSystem::GetLastCandidateCount() const
{
    return lastCandidateCount_;
}
