#pragma once

#include "IScene.h"

class TitleScene final : public IScene
{
public:
    SceneRequest Update(Input& input, float deltaSeconds) override;
    void Draw() const override;
};
