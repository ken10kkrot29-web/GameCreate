#pragma once

#include "ItemTypes.h"
#include <vector>

class Inventory
{
public:
    int Count(ItemId itemId) const;
    void Add(ItemId itemId, int count);
    bool Remove(ItemId itemId, int count);

private:
    ItemStack* Find(ItemId itemId);
    const ItemStack* Find(ItemId itemId) const;

    std::vector<ItemStack> stacks_;
};
