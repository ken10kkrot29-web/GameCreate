#pragma once

#include "DebugViewModel.h"
#include "../Enemy/Enemy.h"
#include "../Game/GameplayState.h"
#include "../Mission/Mission.h"

class Gameplay;

class DebugViewModelBuilder
{
public:
    DebugViewModel Create(const Gameplay& gameplay) const;

private:
    std::string ToText(GameplayState state) const;
    std::string ToText(MissionState state) const;
    std::string ToText(EnemyBehaviorState state) const;
};
