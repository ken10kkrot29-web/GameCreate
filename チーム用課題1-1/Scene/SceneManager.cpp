#include "SceneManager.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "TitleScene.h"

SceneManager::SceneManager()
{
    ChangeScene(SceneId::Title);
}

void SceneManager::Update(Input& input, float deltaSeconds)
{
    const SceneRequest request = currentScene_->Update(input, deltaSeconds);
    if (request.requested)
    {
        ChangeScene(request.destination);
    }
}

void SceneManager::Draw() const
{
    currentScene_->Draw();
}

bool SceneManager::IsExitRequested() const
{
    return exitRequested_;
}

void SceneManager::ChangeScene(SceneId destination)
{
    switch (destination)
    {
    case SceneId::Title:
        currentScene_ = std::make_unique<TitleScene>();
        break;

    case SceneId::Game:
        currentScene_ = std::make_unique<GameScene>(
            [this](const GameResult& result)
            {
                latestResult_ = result;
            });
        break;

    case SceneId::Result:
        currentScene_ = std::make_unique<ResultScene>(latestResult_);
        break;

    case SceneId::Exit:
        exitRequested_ = true;
        break;
    }
}
