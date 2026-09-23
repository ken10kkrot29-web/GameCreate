#pragma once

#include "../Core/Math/Vector2.h"
#include <vector>

struct ExplosionEvent
{
    Vector2 center;
    float radius = 0.0f;
    int damage = 0;
};

struct BombEntity
{
    Vector2 position;
    float remainingFuseSeconds = 1.2f;
    bool removalRequested = false;
};

class PlacedGadgetManager
{
public:
    void RequestBombPlacement(const Vector2& position);
    std::vector<ExplosionEvent> Update(float deltaSeconds);
    void CommitPendingChanges();

    const std::vector<BombEntity>& GetBombs() const;

private:
    static constexpr float ExplosionRadius = 105.0f;
    static constexpr int ExplosionDamage = 3;

    std::vector<BombEntity> bombs_;
    std::vector<BombEntity> pendingBombs_;
};
