#include "Input.h"
#include <DxLib.h>
#include <cmath>
#include <cstring>

namespace
{
    constexpr int AnalogStickDeadZone = 200;
    constexpr float AnalogStickScale = 1000.0f;
}

void Input::ApplyBindings(const InputBindings& bindings)
{
    bindings_ = bindings;
}

void Input::Update()
{
    std::memcpy(previousKeys_, currentKeys_, sizeof(currentKeys_));
    GetHitKeyStateAll(currentKeys_);

    previousPadButtons_ = currentPadButtons_;
    currentPadButtons_ = GetJoypadInputState(DX_INPUT_PAD1);
}

PlayerCommand Input::CreatePlayerCommand() const
{
    PlayerCommand command;

    if (currentKeys_[KEY_INPUT_A] || currentKeys_[KEY_INPUT_LEFT])
    {
        command.moveDirection.x -= 1.0f;
    }
    if (currentKeys_[KEY_INPUT_D] || currentKeys_[KEY_INPUT_RIGHT])
    {
        command.moveDirection.x += 1.0f;
    }
    if (currentKeys_[KEY_INPUT_W] || currentKeys_[KEY_INPUT_UP])
    {
        command.moveDirection.y -= 1.0f;
    }
    if (currentKeys_[KEY_INPUT_S] || currentKeys_[KEY_INPUT_DOWN])
    {
        command.moveDirection.y += 1.0f;
    }

    int analogX = 0;
    int analogY = 0;
    GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

    if (std::abs(analogX) > AnalogStickDeadZone)
    {
        command.moveDirection.x = analogX / AnalogStickScale;
    }
    if (std::abs(analogY) > AnalogStickDeadZone)
    {
        command.moveDirection.y = analogY / AnalogStickScale;
    }

    command.moveDirection = Normalize(command.moveDirection);

    command.attackPressed = IsKeyPressed(KEY_INPUT_Z) || IsPadButtonPressed(PAD_INPUT_A);
    command.dodgePressed = IsKeyPressed(KEY_INPUT_X) || IsPadButtonPressed(PAD_INPUT_B);
    command.interactPressed = IsKeyPressed(KEY_INPUT_E) || IsPadButtonPressed(PAD_INPUT_Y);
    command.useGadgetPressed = IsKeyPressed(KEY_INPUT_C) || IsPadButtonPressed(PAD_INPUT_R);
    command.openCraftMenuPressed = IsKeyPressed(KEY_INPUT_Q) || IsPadButtonPressed(PAD_INPUT_L);
    command.pausePressed = IsKeyPressed(KEY_INPUT_ESCAPE) || IsPadButtonPressed(PAD_INPUT_START);

    return command;
}

bool Input::IsMenuConfirmPressed() const
{
    return IsKeyPressed(KEY_INPUT_RETURN) || IsPadButtonPressed(PAD_INPUT_A);
}

bool Input::IsMenuCancelPressed() const
{
    return IsKeyPressed(KEY_INPUT_ESCAPE) || IsPadButtonPressed(PAD_INPUT_B);
}

bool Input::IsDebugOverlayTogglePressed() const
{
    return IsKeyPressed(KEY_INPUT_F1);
}

bool Input::IsCoordinateDisplayTogglePressed() const
{
    return IsKeyPressed(KEY_INPUT_F2);
}

bool Input::IsCollisionDisplayTogglePressed() const
{
    return IsKeyPressed(KEY_INPUT_F3);
}

bool Input::IsControlHelpTogglePressed() const
{
    return IsKeyPressed(KEY_INPUT_F4);
}

bool Input::IsKeyPressed(int keyCode) const
{
    return currentKeys_[keyCode] && !previousKeys_[keyCode];
}

bool Input::IsPadButtonPressed(int buttonMask) const
{
    const bool isCurrentlyPressed = (currentPadButtons_ & buttonMask) != 0;
    const bool wasPreviouslyPressed = (previousPadButtons_ & buttonMask) != 0;
    return isCurrentlyPressed && !wasPreviouslyPressed;
}
