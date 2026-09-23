#pragma once

#include <algorithm>

enum class DisplayMode
{
    Windowed,
    Fullscreen
};

struct AudioSettings
{
    static constexpr float MinimumVolume = 0.0f;
    static constexpr float MaximumVolume = 1.0f;

    float masterVolume = 1.0f;
    float bgmVolume = 0.8f;
    float soundEffectVolume = 1.0f;
    float ambientVolume = 0.8f;

    void Validate()
    {
        masterVolume = std::clamp(masterVolume, MinimumVolume, MaximumVolume);
        bgmVolume = std::clamp(bgmVolume, MinimumVolume, MaximumVolume);
        soundEffectVolume = std::clamp(soundEffectVolume, MinimumVolume, MaximumVolume);
        ambientVolume = std::clamp(ambientVolume, MinimumVolume, MaximumVolume);
    }
};

struct InputBindings
{
    int attackButton = 0;
    int dodgeButton = 1;
    int interactButton = 3;
    int useGadgetButton = 5;
    int openCraftMenuButton = 4;
    int pauseButton = 7;
};

struct UserSettings
{
    AudioSettings audio;
    DisplayMode displayMode = DisplayMode::Windowed;
    InputBindings inputBindings;
};
