#include "Application/GameApplication.h"
#include "Config/GameConfig.h"
#include "Config/UserSettings.h"
#include <DxLib.h>
//Windowsのスタートボタン(int = この関数が最後に整数値を返す)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    //オブジェクト作成
    UserSettings startupSettings;
    //ゲーム画面の設定
    SetGraphMode(GameConfig::ScreenWidth,GameConfig::ScreenHeight,GameConfig::ColorDepth);
    //現在のディスプレイ設定(? = 三項演算子 = if文)
    ChangeWindowMode(startupSettings.displayMode == DisplayMode::Windowed? TRUE: FALSE);
    //Dxlibの初期化（準備）
    if (DxLib_Init() == -1)
    {
        //失敗でゲーム終了
        return -1;
    }
    //オブジェクト作成
    GameApplication application;
    const int result = application.Run();

    DxLib_End();
    return result;
}
