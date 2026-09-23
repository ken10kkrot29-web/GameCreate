#pragma once

#include "ItemTypes.h"
#include "../Core/Math/Vector2.h"
#include <vector>

struct WorldItem
{
    ItemId itemId = ItemId::Scrap;
    int count = 1;
    Vector2 position;
    bool removalRequested = false;
};

class ItemManager
{
public:
    void RequestSpawn(ItemId itemId, int count, const Vector2& position);
    void CommitPendingChanges();

    std::vector<WorldItem>& GetItems();
    const std::vector<WorldItem>& GetItems() const;

private:
    std::vector<WorldItem> items_;
    std::vector<WorldItem> pendingItems_;
};
