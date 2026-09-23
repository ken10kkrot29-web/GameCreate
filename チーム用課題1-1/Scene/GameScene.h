#pragma once

#include "IScene.h"
#include "../Game/GameResult.h"
#include "../Game/Gameplay.h"
#include "../UI/GameHud.h"
#include "../UI/WorldRenderer.h"
#include "../UI/DebugRenderer.h"
#include "../UI/DebugViewModelBuilder.h"
#include <functional>

class GameScene final : public IScene
{
public:
    using ResultReceiver = std::function<void(const GameResult&)>;

    explicit GameScene(ResultReceiver resultReceiver);

    SceneRequest Update(Input& input, float deltaSeconds) override;
    void Draw() const override;

private:
    Gameplay gameplay_;
    WorldRenderer worldRenderer_;
    GameHud gameHud_;
    DebugViewModelBuilder debugViewModelBuilder_;
    DebugRenderer debugRenderer_;
    DebugDisplaySettings debugDisplaySettings_;
    ResultReceiver resultReceiver_;
};
