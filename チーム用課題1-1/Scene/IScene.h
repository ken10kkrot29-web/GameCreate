#pragma once

#include "SceneTypes.h"

class Input;

class IScene
{
public:
    virtual ~IScene() = default;

    virtual SceneRequest Update(Input& input, float deltaSeconds) = 0;
    virtual void Draw() const = 0;
};
