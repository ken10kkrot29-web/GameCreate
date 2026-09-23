#pragma once

#include "../Core/Math/Vector2.h"

struct PlayerCommand
{
    Vector2 moveDirection;
    bool attackPressed = false;
    bool dodgePressed = false;
    bool interactPressed = false;
    bool useGadgetPressed = false;
    bool openCraftMenuPressed = false;
    bool pausePressed = false;
};
