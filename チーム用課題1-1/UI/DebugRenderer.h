#pragma once

#include "DebugViewModel.h"

class Camera;

class DebugRenderer
{
public:
    void Draw(const DebugViewModel& viewModel,const DebugDisplaySettings& settings,const Camera& camera) const;

private:
    void DrawStatusPanel(const DebugViewModel& viewModel) const;
    void DrawCoordinateLabels(const DebugViewModel& viewModel,const Camera& camera) const;
    void DrawCollisionBounds(const DebugViewModel& viewModel,const Camera& camera) const;
    void DrawControlHelp() const;
};
