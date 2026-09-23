#pragma once

#include "IScene.h"
#include "../Game/GameResult.h"
#include <memory>

class SceneManager
{
public:
    SceneManager();

    void Update(Input& input, float deltaSeconds);
    void Draw() const;
    bool IsExitRequested() const;

private:
    void ChangeScene(SceneId destination);

    std::unique_ptr<IScene> currentScene_;
    GameResult latestResult_;
    bool exitRequested_ = false;
};
