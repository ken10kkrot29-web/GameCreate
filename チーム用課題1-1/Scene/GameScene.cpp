#include "GameScene.h"
#include "../Input/Input.h"
#include <DxLib.h>

GameScene::GameScene(ResultReceiver resultReceiver): resultReceiver_(std::move(resultReceiver))
{
}

SceneRequest GameScene::Update(Input& input, float deltaSeconds)
{
    if (input.IsDebugOverlayTogglePressed())
    {
        debugDisplaySettings_.showOverlay =!debugDisplaySettings_.showOverlay;
    }
    if (input.IsCoordinateDisplayTogglePressed())
    {
        debugDisplaySettings_.showCoordinates =!debugDisplaySettings_.showCoordinates;
    }
    if (input.IsCollisionDisplayTogglePressed())
    {
        debugDisplaySettings_.showCollisionBounds =!debugDisplaySettings_.showCollisionBounds;
    }
    if (input.IsControlHelpTogglePressed())
    {
        debugDisplaySettings_.showControlHelp =!debugDisplaySettings_.showControlHelp;
    }

    const PlayerCommand command = input.CreatePlayerCommand();
    gameplay_.Update(command, deltaSeconds);

    const GameplayState state = gameplay_.GetState();
    if (state == GameplayState::MissionCleared || state == GameplayState::GameOver)
    {
        resultReceiver_(gameplay_.CreateResult());
        return { SceneId::Result, true };
    }

    return {};
}

void GameScene::Draw() const
{
    worldRenderer_.Draw(gameplay_);
    gameHud_.Draw(gameplay_.CreateHudViewModel());

    const DebugViewModel debugViewModel =debugViewModelBuilder_.Create(gameplay_);
    debugRenderer_.Draw(debugViewModel,debugDisplaySettings_,gameplay_.GetCamera());

    if (gameplay_.GetState() == GameplayState::Crafting)
    {
        DrawBox(360, 180, 920, 540, GetColor(10, 10, 20), TRUE);
        DrawString(420, 230, "CRAFT MENU", GetColor(255, 255, 255));
        DrawString(420, 290, "Bomb: 2 Scrap (Z / Pad A)", GetColor(255, 255, 255));
        DrawString(420, 350, "Q / Pad L: Close", GetColor(200, 200, 200));
    }

    if (gameplay_.GetState() == GameplayState::Paused)
    {
        DrawBox(430, 260, 850, 460, GetColor(10, 10, 10), TRUE);
        DrawString(570, 330, "PAUSED", GetColor(255, 255, 255));
        DrawString(505, 380, "ESC / START: Resume", GetColor(200, 200, 200));
    }
}
