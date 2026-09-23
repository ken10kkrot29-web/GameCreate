#include "GameApplication.h"
#include "../Config/GameConfig.h"
#include <DxLib.h>
//Run関数の定義
int GameApplication::Run()
{
    //プレイヤーの操作設定を入力システムへ渡す
    input_.ApplyBindings(settings_.inputBindings);
    //画面の表裏で切り替え
    SetDrawScreen(DX_SCREEN_BACK);
    //フレームの更新（浮動小数点数型への置き換え）
    //conatexpr = コンパイル時に値を決められる定数
    constexpr float FixedDeltaSeconds =1.0f / static_cast<float>(GameConfig::TargetFps);
    constexpr int FrameBudgetMilliseconds =1000 / GameConfig::TargetFps;

    while (ProcessMessage() == 0 && !sceneManager_.IsExitRequested())
    {
        const int frameStartTime = GetNowCount();

        input_.Update();
        sceneManager_.Update(input_, FixedDeltaSeconds);

        ClearDrawScreen();
        sceneManager_.Draw();
        ScreenFlip();

        const int elapsedMilliseconds = GetNowCount() - frameStartTime;
        if (elapsedMilliseconds < FrameBudgetMilliseconds)
        {
            WaitTimer(FrameBudgetMilliseconds - elapsedMilliseconds);
        }
    }
    return 0;
}
