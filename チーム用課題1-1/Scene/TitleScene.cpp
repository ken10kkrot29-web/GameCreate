#include "TitleScene.h"
#include "../Input/Input.h"
#include <DxLib.h>

SceneRequest TitleScene::Update(Input& input, float)
{
    if (input.IsMenuConfirmPressed())
    {
        return { SceneId::Game, true };
    }

    if (input.IsMenuCancelPressed())
    {
        return { SceneId::Exit, true };
    }

    return {};
}

void TitleScene::Draw() const
{
    DrawString(465,240,"INFILTRATION TRIAL",GetColor(255, 255, 255));
    DrawString(480,320,"ENTER / PAD A : START",GetColor(180, 220, 255));
    DrawString(480,370,"ESC / PAD B : EXIT",GetColor(180, 180, 180));
}
