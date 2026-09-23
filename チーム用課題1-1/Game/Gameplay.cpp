#include "Gameplay.h"
#include "../Core/Collision/Collision.h"

Gameplay::Gameplay(): enemyManager_(EnemyDefinition{})
{
    enemyManager_.Spawn({ 330.0f, 260.0f });
    enemyManager_.Spawn({ 380.0f, 480.0f });
    enemyManager_.Spawn({ 1120.0f, 360.0f });

    camera_.Follow(player_.GetPosition(),field_.GetWidth(),field_.GetHeight());
}

void Gameplay::Update(const PlayerCommand& command,float deltaSeconds)
{
    if (state_ == GameplayState::MissionCleared || state_ == GameplayState::GameOver)
    {
        return;
    }

    if (command.pausePressed)
    {
        state_ = state_ == GameplayState::Paused? GameplayState::Playing: GameplayState::Paused;
        return;
    }

    if (state_ == GameplayState::Paused)
    {
        return;
    }

    if (command.openCraftMenuPressed)
    {
        state_ = state_ == GameplayState::Crafting ? GameplayState::Playing : GameplayState::Crafting;
    }

    if (state_ == GameplayState::Crafting)
    {
        UpdateCrafting(command);
        return;
    }
    UpdatePlaying(command, deltaSeconds);
}

void Gameplay::UpdatePlaying(const PlayerCommand& command,float deltaSeconds)
{
    elapsedSeconds_ += deltaSeconds;

    const Vector2 previousPlayerPosition = player_.GetPosition();
    player_.Update(command, deltaSeconds);
    ResolvePlayerAgainstField(previousPlayerPosition);

    if (!player_.IsAttackActive())
    {
        knifeHitConsumed_ = false;
    }

    if (command.useGadgetPressed && inventory_.Remove(ItemId::Bomb, 1))
    {
        gadgetManager_.RequestBombPlacement(player_.GetPosition());
    }

    enemyManager_.Update(player_.GetPosition(),field_,deltaSeconds);

    ProcessKnifeHits();
    ProcessEnemyContact();
    ProcessItemPickups();

    const std::vector<ExplosionEvent> explosionEvents =gadgetManager_.Update(deltaSeconds);
    ProcessExplosions(explosionEvents);
    ProcessInteraction(command);

    CommitPendingChanges();

    camera_.Follow(player_.GetPosition(),field_.GetWidth(),field_.GetHeight());

    if (player_.IsDead())
    {
        state_ = GameplayState::GameOver;
    }
    else if (mission_.IsCleared())
    {
        state_ = GameplayState::MissionCleared;
    }
}

void Gameplay::UpdateCrafting(const PlayerCommand& command)
{
    if (command.attackPressed)
    {
        craftSystem_.Craft(craftSystem_.GetBombRecipe(),inventory_);
    }
}

void Gameplay::ResolvePlayerAgainstField(const Vector2& previousPosition)
{
    const Vector2 constrainedPosition = field_.ConstrainPosition(player_.GetPosition(),14.0f);
    player_.StopAt(constrainedPosition);

    if (field_.CollidesWithSolidObject(player_.GetCollisionBounds()))
    {
        player_.StopAt(previousPosition);
    }
}

void Gameplay::ProcessKnifeHits()
{
    if (knifeHitConsumed_)
    {
        return;
    }

    const std::vector<EnemyHitEvent> events =collisionSystem_.FindKnifeHits(player_, enemyManager_);

    if (events.empty())
    {
        return;
    }

    std::vector<Enemy>& enemies = enemyManager_.GetEnemies();
    for (const EnemyHitEvent& event : events)
    {
        Enemy& enemy = enemies[event.enemyIndex];
        enemy.ApplyDamage(event.damage);

        if (enemy.IsDead())
        {
            itemManager_.RequestSpawn(ItemId::Scrap,1,enemy.GetPosition());
            enemy.RequestRemoval();
            ++defeatedEnemyCount_;
        }
    }
    knifeHitConsumed_ = true;
}

void Gameplay::ProcessEnemyContact()
{
    if (collisionSystem_.IsPlayerTouchingEnemy(player_, enemyManager_))
    {
        player_.ApplyDamage(1);
    }
}

void Gameplay::ProcessItemPickups()
{
    const std::vector<ItemPickupEvent> events =collisionSystem_.FindItemPickups(player_, itemManager_);

    std::vector<WorldItem>& items = itemManager_.GetItems();
    for (const ItemPickupEvent& event : events)
    {
        WorldItem& item = items[event.itemIndex];
        inventory_.Add(item.itemId, item.count);
        item.removalRequested = true;
    }
}

void Gameplay::ProcessExplosions(const std::vector<ExplosionEvent>& events)
{
    std::vector<Enemy>& enemies = enemyManager_.GetEnemies();

    for (const ExplosionEvent& event : events)
    {
        if (!field_.IsBreakableWallDestroyed()&& Collision::IntersectsCircle(event.center,event.radius,Center(field_.GetBreakableWallBounds()),field_.GetBreakableWallBounds().width * 0.5f))
        {
            field_.DestroyBreakableWall();
        }

        for (Enemy& enemy : enemies)
        {
            if (enemy.IsDead() || enemy.IsRemovalRequested())
            {
                continue;
            }

            if (!Collision::IntersectsCircle(event.center,event.radius,enemy.GetPosition(),enemy.GetCollisionRadius()))
            {
                continue;
            }

            enemy.ApplyDamage(event.damage);
            if (enemy.IsDead())
            {
                itemManager_.RequestSpawn(ItemId::Scrap,1,enemy.GetPosition());
                enemy.RequestRemoval();
                ++defeatedEnemyCount_;
            }
        }
    }
}

void Gameplay::ProcessInteraction(const PlayerCommand& command)
{
    if (!command.interactPressed)
    {
        return;
    }

    const Rect playerBounds = player_.GetCollisionBounds();

    if (field_.IsBreakableWallDestroyed() && Collision::Intersects(playerBounds,field_.GetMissionTargetBounds()))
    {
        mission_.NotifyTargetInteracted();
    }

    if (Collision::Intersects(playerBounds,field_.GetExtractionBounds()))
    {
        mission_.NotifyExtractionInteracted();
    }
}

void Gameplay::CommitPendingChanges()
{
    itemManager_.CommitPendingChanges();
    gadgetManager_.CommitPendingChanges();
    enemyManager_.CommitRemovals();
}

GameplayState Gameplay::GetState() const { return state_; }

GameResult Gameplay::CreateResult() const
{
    return
    {
        state_ == GameplayState::MissionCleared,
        defeatedEnemyCount_,
        elapsedSeconds_
    };
}

HudViewModel Gameplay::CreateHudViewModel() const
{
    HudViewModel viewModel;
    viewModel.playerHp = player_.GetHp();
    viewModel.playerMaxHp = player_.GetMaxHp();
    viewModel.scrapCount = inventory_.Count(ItemId::Scrap);
    viewModel.bombCount = inventory_.Count(ItemId::Bomb);
    viewModel.enemyCount = static_cast<int>(enemyManager_.GetEnemies().size());
    viewModel.updatedEnemyCount = enemyManager_.GetUpdatedEnemyCount();
    viewModel.collisionCandidateCount = collisionSystem_.GetLastCandidateCount();

    switch (mission_.GetState())
    {
    case MissionState::ReachTarget:
        viewModel.missionText = "Craft a bomb, breach the wall, and access the target.";
        break;
    case MissionState::ReachExtraction:
        viewModel.missionText = "Reach the extraction point.";
        break;
    case MissionState::Cleared:
        viewModel.missionText = "Mission complete.";
        break;
    }

    return viewModel;
}

const Player& Gameplay::GetPlayer() const { return player_; }
const EnemyManager& Gameplay::GetEnemyManager() const { return enemyManager_; }
const Field& Gameplay::GetField() const { return field_; }
const ItemManager& Gameplay::GetItemManager() const { return itemManager_; }
const Inventory& Gameplay::GetInventory() const { return inventory_; }
const PlacedGadgetManager& Gameplay::GetGadgetManager() const { return gadgetManager_; }
const Camera& Gameplay::GetCamera() const { return camera_; }
MissionState Gameplay::GetMissionState() const { return mission_.GetState(); }
int Gameplay::GetDefeatedEnemyCount() const { return defeatedEnemyCount_; }
float Gameplay::GetElapsedSeconds() const { return elapsedSeconds_; }
