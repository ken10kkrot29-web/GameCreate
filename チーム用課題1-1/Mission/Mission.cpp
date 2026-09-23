#include "Mission.h"

void Mission::NotifyTargetInteracted()
{
    if (state_ == MissionState::ReachTarget)
    {
        state_ = MissionState::ReachExtraction;
    }
}

void Mission::NotifyExtractionInteracted()
{
    if (state_ == MissionState::ReachExtraction)
    {
        state_ = MissionState::Cleared;
    }
}

MissionState Mission::GetState() const { return state_; }
bool Mission::IsCleared() const { return state_ == MissionState::Cleared; }
