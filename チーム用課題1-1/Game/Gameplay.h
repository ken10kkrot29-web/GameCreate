#pragma once

#include "GameResult.h"
#include "GameplayState.h"
#include "../Craft/CraftSystem.h"
#include "../Enemy/EnemyManager.h"
#include "../Field/Field.h"
#include "../Gadget/PlacedGadgetManager.h"
#include "../Input/PlayerCommand.h"
#include "../Item/Inventory.h"
#include "../Item/ItemManager.h"
#include "../Mission/Mission.h"
#include "../Player/Player.h"
#include "../System/Camera.h"
#include "../System/CollisionSystem.h"
#include "../UI/HudViewModel.h"

class Gameplay
{
public:
    Gameplay();

    void Update(const PlayerCommand& command, float deltaSeconds);

    GameplayState GetState() const;
    GameResult CreateResult() const;
    HudViewModel CreateHudViewModel() const;

    const Player& GetPlayer() const;
    const EnemyManager& GetEnemyManager() const;
    const Field& GetField() const;
    const ItemManager& GetItemManager() const;
    const Inventory& GetInventory() const;
    const PlacedGadgetManager& GetGadgetManager() const;
    const Camera& GetCamera() const;
    MissionState GetMissionState() const;
    int GetDefeatedEnemyCount() const;
    float GetElapsedSeconds() const;

private:
    void UpdatePlaying(const PlayerCommand& command, float deltaSeconds);
    void UpdateCrafting(const PlayerCommand& command);
    void ResolvePlayerAgainstField(const Vector2& previousPosition);
    void ProcessKnifeHits();
    void ProcessEnemyContact();
    void ProcessItemPickups();
    void ProcessExplosions(const std::vector<ExplosionEvent>& events);
    void ProcessInteraction(const PlayerCommand& command);
    void CommitPendingChanges();

    Player player_;
    EnemyManager enemyManager_;
    Field field_;
    ItemManager itemManager_;
    Inventory inventory_;
    CraftSystem craftSystem_;
    Mission mission_;
    PlacedGadgetManager gadgetManager_;
    CollisionSystem collisionSystem_;
    Camera camera_;
    GameplayState state_ = GameplayState::Playing;
    float elapsedSeconds_ = 0.0f;
    int defeatedEnemyCount_ = 0;
    bool knifeHitConsumed_ = false;
};
