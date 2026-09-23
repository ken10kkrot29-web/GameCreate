#include "ResultScene.h"
#include "../Input/Input.h"
#include <DxLib.h>

ResultScene::ResultScene(const GameResult& result) : result_(result)
{
}

SceneRequest ResultScene::Update(Input& input, float)
{
    if (input.IsMenuConfirmPressed())
    {
        return { SceneId::Game, true };
    }

    if (input.IsMenuCancelPressed())
    {
        return { SceneId::Title, true };
    }

    return {};
}

void ResultScene::Draw() const
{
    DrawString(520,230,result_.missionCleared ? "MISSION CLEAR" : "GAME OVER",result_.missionCleared ? GetColor(80, 240, 160) : GetColor(240, 80, 80));

    DrawFormatString(500,300,GetColor(255, 255, 255),"Enemies: %d",result_.defeatedEnemyCount);
    DrawFormatString(500,340,GetColor(255, 255, 255),"Time: %.1f sec",result_.elapsedSeconds);
    DrawString(450,410,"ENTER: Restart    ESC: Title",GetColor(200, 220, 255));
}
