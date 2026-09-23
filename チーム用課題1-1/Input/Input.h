#pragma once

#include "../Config/UserSettings.h"
#include "PlayerCommand.h"

class Input
{
public:
    void ApplyBindings(const InputBindings& bindings);
    void Update();

    PlayerCommand CreatePlayerCommand() const;

    bool IsMenuConfirmPressed() const;
    bool IsMenuCancelPressed() const;
    bool IsDebugOverlayTogglePressed() const;
    bool IsCoordinateDisplayTogglePressed() const;
    bool IsCollisionDisplayTogglePressed() const;
    bool IsControlHelpTogglePressed() const;

private:
    bool IsKeyPressed(int keyCode) const;
    bool IsPadButtonPressed(int buttonMask) const;

    InputBindings bindings_;
    char currentKeys_[256] = {};
    char previousKeys_[256] = {};
    int currentPadButtons_ = 0;
    int previousPadButtons_ = 0;
};
