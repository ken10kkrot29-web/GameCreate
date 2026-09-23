#pragma once

#include "../Core/Math/Vector2.h"
#include <vector>

class Player;
class EnemyManager;
class ItemManager;

struct EnemyHitEvent
{
    std::size_t enemyIndex = 0;
    int damage = 0;
};

struct ItemPickupEvent
{
    std::size_t itemIndex = 0;
};

class CollisionSystem
{
public:
    std::vector<EnemyHitEvent> FindKnifeHits(const Player& player,const EnemyManager& enemies) const;

    std::vector<ItemPickupEvent> FindItemPickups(const Player& player,const ItemManager& items) const;

    bool IsPlayerTouchingEnemy(const Player& player,const EnemyManager& enemies) const;

    int GetLastCandidateCount() const;

private:
    static constexpr int KnifeDamage = 1;
    mutable int lastCandidateCount_ = 0;
};
