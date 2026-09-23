#include "PlacedGadgetManager.h"
#include <algorithm>

void PlacedGadgetManager::RequestBombPlacement(const Vector2& position)
{
    pendingBombs_.push_back({ position });
}

std::vector<ExplosionEvent> PlacedGadgetManager::Update(float deltaSeconds)
{
    std::vector<ExplosionEvent> events;

    for (BombEntity& bomb : bombs_)
    {
        bomb.remainingFuseSeconds -= deltaSeconds;
        if (bomb.remainingFuseSeconds > 0.0f)
        {
            continue;
        }

        events.push_back({bomb.position,ExplosionRadius,ExplosionDamage});
        bomb.removalRequested = true;
    }
    return events;
}

void PlacedGadgetManager::CommitPendingChanges()
{
    bombs_.insert(bombs_.end(),pendingBombs_.begin(),pendingBombs_.end());
    pendingBombs_.clear();

    std::erase_if(bombs_, [](const BombEntity& bomb)
    {
        return bomb.removalRequested;
    });
}

const std::vector<BombEntity>& PlacedGadgetManager::GetBombs() const
{
    return bombs_;
}
