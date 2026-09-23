#pragma once

enum class MissionState
{
    ReachTarget,
    ReachExtraction,
    Cleared
};

class Mission
{
public:
    void NotifyTargetInteracted();
    void NotifyExtractionInteracted();

    MissionState GetState() const;
    bool IsCleared() const;

private:
    MissionState state_ = MissionState::ReachTarget;
};
