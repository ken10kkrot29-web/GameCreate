#pragma once

#include "IScene.h"
#include "../Game/GameResult.h"

class ResultScene final : public IScene
{
public:
    explicit ResultScene(const GameResult& result);

    SceneRequest Update(Input& input, float deltaSeconds) override;
    void Draw() const override;

private:
    GameResult result_;
};
