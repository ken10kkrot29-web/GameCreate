#pragma once

#include "../Config/UserSettings.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"

class GameApplication
{
public:
    int Run();

private:
    UserSettings settings_;
    Input input_;
    SceneManager sceneManager_;
};
