#include "Inventory.h"
#include <algorithm>

int Inventory::Count(ItemId itemId) const
{
    const ItemStack* stack = Find(itemId);
    return stack == nullptr ? 0 : stack->count;
}

void Inventory::Add(ItemId itemId, int count)
{
    if (count <= 0)
    {
        return;
    }

    ItemStack* stack = Find(itemId);
    if (stack == nullptr)
    {
        stacks_.push_back({ itemId, count });
        return;
    }

    stack->count += count;
}

bool Inventory::Remove(ItemId itemId, int count)
{
    if (count <= 0)
    {
        return false;
    }

    ItemStack* stack = Find(itemId);
    if (stack == nullptr || stack->count < count)
    {
        return false;
    }

    stack->count -= count;
    return true;
}

ItemStack* Inventory::Find(ItemId itemId)
{
    const auto iterator = std::find_if(
        stacks_.begin(),
        stacks_.end(),
        [itemId](const ItemStack& stack)
        {
            return stack.itemId == itemId;
        });

    return iterator == stacks_.end() ? nullptr : &(*iterator);
}

const ItemStack* Inventory::Find(ItemId itemId) const
{
    const auto iterator = std::find_if(
        stacks_.begin(),
        stacks_.end(),
        [itemId](const ItemStack& stack)
        {
            return stack.itemId == itemId;
        });

    return iterator == stacks_.end() ? nullptr : &(*iterator);
}
