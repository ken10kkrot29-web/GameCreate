#include "ItemManager.h"
#include <algorithm>

void ItemManager::RequestSpawn(ItemId itemId,int count,const Vector2& position)
{
    pendingItems_.push_back({ itemId, count, position, false });
}

void ItemManager::CommitPendingChanges()
{
    items_.insert(items_.end(),
        pendingItems_.begin(),
        pendingItems_.end());
    pendingItems_.clear();

    std::erase_if(items_, [](const WorldItem& item)
    {
        return item.removalRequested;
    });
}

std::vector<WorldItem>& ItemManager::GetItems() { return items_; }
const std::vector<WorldItem>& ItemManager::GetItems() const { return items_; }
