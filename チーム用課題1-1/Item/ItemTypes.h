#pragma once

enum class ItemId
{
    Scrap,
    Bomb
};

struct ItemStack
{
    ItemId itemId = ItemId::Scrap;
    int count = 0;
};
