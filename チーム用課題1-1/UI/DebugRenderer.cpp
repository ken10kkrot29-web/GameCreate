#include "DebugRenderer.h"
#include "../System/Camera.h"
#include <DxLib.h>

void DebugRenderer::Draw(const DebugViewModel& viewModel,const DebugDisplaySettings& settings,const Camera& camera) const
{
    if (settings.showOverlay)
    {
        DrawStatusPanel(viewModel);
    }

    if (settings.showCoordinates)
    {
        DrawCoordinateLabels(viewModel, camera);
    }

    if (settings.showCollisionBounds)
    {
        DrawCollisionBounds(viewModel, camera);
    }

    if (settings.showControlHelp)
    {
        DrawControlHelp();
    }
}

void DebugRenderer::DrawStatusPanel(const DebugViewModel& viewModel) const
{
    constexpr int PanelLeft = 890;
    constexpr int PanelTop = 10;
    constexpr int PanelRight = 1270;
    constexpr int PanelBottom = 220;
    constexpr int TextLeft = 910;

    DrawBox(PanelLeft,PanelTop,PanelRight,PanelBottom,GetColor(12, 18, 24),TRUE);
    DrawBox(PanelLeft,PanelTop,PanelRight,PanelBottom,GetColor(100, 180, 220),FALSE);

    const int white = GetColor(255, 255, 255);
    DrawString(TextLeft, 25, "DEBUG STATUS", white);
    DrawFormatString(TextLeft, 52, white, "Gameplay: %s",viewModel.gameplayStateText.c_str());
    DrawFormatString(TextLeft, 74, white, "Mission: %s",viewModel.missionStateText.c_str());
    DrawFormatString(TextLeft, 96, white, "Camera: (%.1f, %.1f)",viewModel.cameraPosition.x, viewModel.cameraPosition.y);
    DrawFormatString(TextLeft, 118, white, "Enemy: %d / updated %d",viewModel.enemyCount, viewModel.updatedEnemyCount);
    DrawFormatString(TextLeft, 140, white, "Item: %d   Bomb: %d",viewModel.itemCount, viewModel.bombCount);
    DrawFormatString(TextLeft, 162, white, "Defeated: %d",viewModel.defeatedEnemyCount);
    DrawFormatString(TextLeft, 184, white, "Elapsed: %.2f sec",viewModel.elapsedSeconds);
}

void DebugRenderer::DrawCoordinateLabels(const DebugViewModel& viewModel,const Camera& camera) const
{
    for (const DebugPointView& point : viewModel.points)
    {
        const Vector2 screen = camera.WorldToScreen(point.worldPosition);

        DrawFormatString(static_cast<int>(screen.x + 18.0f),static_cast<int>(screen.y - 18.0f),GetColor(255, 255, 255),"%s (%.1f, %.1f)",point.label.c_str(),point.worldPosition.x,point.worldPosition.y);
        DrawString(static_cast<int>(screen.x + 18.0f),static_cast<int>(screen.y + 2.0f),point.stateText.c_str(),GetColor(210, 230, 255));
    }
}

void DebugRenderer::DrawCollisionBounds(const DebugViewModel& viewModel,const Camera& camera) const
{
    for (const DebugRectView& rectView : viewModel.collisionRects)
    {
        const Vector2 topLeft = camera.WorldToScreen({rectView.worldBounds.x,rectView.worldBounds.y});

        DrawBox(static_cast<int>(topLeft.x),static_cast<int>(topLeft.y),static_cast<int>(topLeft.x + rectView.worldBounds.width),static_cast<int>(topLeft.y + rectView.worldBounds.height),GetColor(50, 255, 120),FALSE);
    }

    constexpr float HalfAngleCosine = 0.7071067f;
    for (const EnemyVisionView& vision : viewModel.enemyVisions)
    {
        const Vector2 leftDirection = {vision.facingDirection.x * HalfAngleCosine- vision.facingDirection.y * HalfAngleCosine,vision.facingDirection.x * HalfAngleCosine+ vision.facingDirection.y * HalfAngleCosine};
        const Vector2 rightDirection = {vision.facingDirection.x * HalfAngleCosine+ vision.facingDirection.y * HalfAngleCosine, -vision.facingDirection.x * HalfAngleCosine + vision.facingDirection.y * HalfAngleCosine};

        const Vector2 origin = camera.WorldToScreen(vision.origin);
        const Vector2 leftEnd = camera.WorldToScreen(vision.origin + leftDirection * vision.viewDistance);
        const Vector2 rightEnd = camera.WorldToScreen(vision.origin + rightDirection * vision.viewDistance);

        DrawLine(static_cast<int>(origin.x),static_cast<int>(origin.y),static_cast<int>(leftEnd.x),static_cast<int>(leftEnd.y),GetColor(255, 180, 30));
        DrawLine(static_cast<int>(origin.x),static_cast<int>(origin.y),static_cast<int>(rightEnd.x),static_cast<int>(rightEnd.y),GetColor(255, 180, 30));
    }
}

void DebugRenderer::DrawControlHelp() const
{
    constexpr int Left = 10;
    constexpr int Top = 520;
    constexpr int Right = 430;
    constexpr int Bottom = 710;

    DrawBox(Left, Top, Right, Bottom, GetColor(12, 18, 24), TRUE);
    DrawBox(Left, Top, Right, Bottom, GetColor(150, 150, 150), FALSE);

    const int white = GetColor(255, 255, 255);
    DrawString(25, 535, "CONTROLS", white);
    DrawString(25, 560, "Move: WASD / Arrow / Left Stick", white);
    DrawString(25, 582, "Attack: Z / Pad A    Dodge: X / Pad B", white);
    DrawString(25, 604, "Interact: E / Pad Y  Bomb: C / Pad R", white);
    DrawString(25, 626, "Craft: Q / Pad L     Pause: ESC / Start", white);
    DrawString(25, 654, "F1 Status  F2 Coordinates",GetColor(150, 220, 255));
    DrawString(25, 676, "F3 Collision  F4 This help",GetColor(150, 220, 255));
}
