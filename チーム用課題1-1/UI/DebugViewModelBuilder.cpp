#include "DebugViewModelBuilder.h"
#include "../Enemy/EnemyManager.h"
#include "../Game/Gameplay.h"
#include <format>

DebugViewModel DebugViewModelBuilder::Create(const Gameplay& gameplay) const
{
    constexpr float EnemyViewDistance = 280.0f;

    DebugViewModel viewModel;
    viewModel.cameraPosition = gameplay.GetCamera().GetPosition();
    viewModel.gameplayStateText = ToText(gameplay.GetState());
    viewModel.missionStateText = ToText(gameplay.GetMissionState());
    viewModel.enemyCount = static_cast<int>(gameplay.GetEnemyManager().GetEnemies().size());
    viewModel.updatedEnemyCount =gameplay.GetEnemyManager().GetUpdatedEnemyCount();
    viewModel.itemCount = static_cast<int>(gameplay.GetItemManager().GetItems().size());
    viewModel.bombCount = static_cast<int>(gameplay.GetGadgetManager().GetBombs().size());
    viewModel.defeatedEnemyCount = gameplay.GetDefeatedEnemyCount();
    viewModel.elapsedSeconds = gameplay.GetElapsedSeconds();

    const Player& player = gameplay.GetPlayer();
    viewModel.points.push_back({"Player",player.GetPosition(),std::format("HP {}/{}", player.GetHp(), player.GetMaxHp())});
    viewModel.collisionRects.push_back({"Player collision",player.GetCollisionBounds()});

    const std::vector<Enemy>& enemies =gameplay.GetEnemyManager().GetEnemies();
    for (std::size_t index = 0; index < enemies.size(); ++index)
    {
        const Enemy& enemy = enemies[index];
        viewModel.points.push_back({std::format("Enemy {}", index),enemy.GetPosition(), std::format("{} awareness {:.2f}",ToText(enemy.GetState()),enemy.GetAwareness())});

        const float radius = enemy.GetCollisionRadius();
        viewModel.collisionRects.push_back({std::format("Enemy {} collision", index),{enemy.GetPosition().x - radius,enemy.GetPosition().y - radius,radius * 2.0f,radius * 2.0f}});

        viewModel.enemyVisions.push_back({enemy.GetPosition(),enemy.GetFacingDirection(),EnemyViewDistance});
    }

    const std::vector<WorldItem>& items =gameplay.GetItemManager().GetItems();
    for (std::size_t index = 0; index < items.size(); ++index)
    {
        viewModel.points.push_back({std::format("WorldItem {}", index),items[index].position,std::format("count {}", items[index].count)});
    }

    const std::vector<BombEntity>& bombs =gameplay.GetGadgetManager().GetBombs();
    for (std::size_t index = 0; index < bombs.size(); ++index)
    {
        viewModel.points.push_back({std::format("Bomb {}", index),bombs[index].position,std::format("fuse {:.2f}", bombs[index].remainingFuseSeconds)});
    }

    const Field& field = gameplay.GetField();
    viewModel.collisionRects.push_back({"BreakableWall",field.GetBreakableWallBounds()});
    viewModel.collisionRects.push_back({"MissionTarget",field.GetMissionTargetBounds()});
    viewModel.collisionRects.push_back({"Extraction",field.GetExtractionBounds()});

    return viewModel;
}

std::string DebugViewModelBuilder::ToText(GameplayState state) const
{
    switch (state)
    {
    case GameplayState::Playing: return "Playing";
    case GameplayState::Crafting: return "Crafting";
    case GameplayState::Paused: return "Paused";
    case GameplayState::MissionCleared: return "MissionCleared";
    case GameplayState::GameOver: return "GameOver";
    }
    return "Unknown";
}

std::string DebugViewModelBuilder::ToText(MissionState state) const
{
    switch (state)
    {
    case MissionState::ReachTarget: return "ReachTarget";
    case MissionState::ReachExtraction: return "ReachExtraction";
    case MissionState::Cleared: return "Cleared";
    }
    return "Unknown";
}

std::string DebugViewModelBuilder::ToText(EnemyBehaviorState state) const
{
    switch (state)
    {
    case EnemyBehaviorState::Patrol: return "Patrol";
    case EnemyBehaviorState::Suspicious: return "Suspicious";
    case EnemyBehaviorState::Alert: return "Alert";
    case EnemyBehaviorState::Chase: return "Chase";
    case EnemyBehaviorState::Attack: return "Attack";
    case EnemyBehaviorState::Damage: return "Damage";
    case EnemyBehaviorState::Dead: return "Dead";
    }
    return "Unknown";
}
