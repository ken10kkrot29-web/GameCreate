#include "CraftSystem.h"
#include "../Item/Inventory.h"

CraftSystem::CraftSystem()
{
    bombRecipe_.ingredients.push_back({ ItemId::Scrap, 2 });
    bombRecipe_.result = { ItemId::Bomb, 1 };
}

bool CraftSystem::CanCraft(const Recipe& recipe,const Inventory& inventory) const
{
    for (const Ingredient& ingredient : recipe.ingredients)
    {
        if (inventory.Count(ingredient.itemId) < ingredient.count)
        {
            return false;
        }
    }
    return true;
}

CraftResult CraftSystem::Craft(const Recipe& recipe,Inventory& inventory) const
{
    if (!CanCraft(recipe, inventory))
    {
        return CraftResult::MissingMaterials;
    }

    for (const Ingredient& ingredient : recipe.ingredients)
    {
        inventory.Remove(ingredient.itemId, ingredient.count);
    }

    inventory.Add(recipe.result.itemId, recipe.result.count);
    return CraftResult::Success;
}

const Recipe& CraftSystem::GetBombRecipe() const
{
    return bombRecipe_;
}
