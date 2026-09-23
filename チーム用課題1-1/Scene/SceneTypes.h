#pragma once

enum class SceneId
{
    Title,
    Game,
    Result,
    Exit
};

struct SceneRequest
{
    SceneId destination = SceneId::Title;
    bool requested = false;
};
