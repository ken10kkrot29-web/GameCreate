#pragma once

#include "../Item/ItemTypes.h"
#include <vector>

class Inventory;

struct Ingredient
{
    ItemId itemId = ItemId::Scrap;
    int count = 0;
};

struct Recipe
{
    std::vector<Ingredient> ingredients;
    ItemStack result;
};

enum class CraftResult
{
    Success,
    MissingMaterials
};

class CraftSystem
{
public:
    CraftSystem();

    bool CanCraft(const Recipe& recipe, const Inventory& inventory) const;
    CraftResult Craft(const Recipe& recipe, Inventory& inventory) const;
    const Recipe& GetBombRecipe() const;

private:
    Recipe bombRecipe_;
};
