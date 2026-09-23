#pragma once

#include "../Core/Math/Rect.h"
#include <string>
#include <vector>

struct DebugPointView
{
    std::string label;
    Vector2 worldPosition;
    std::string stateText;
};

struct DebugRectView
{
    std::string label;
    Rect worldBounds;
};

struct EnemyVisionView
{
    Vector2 origin;
    Vector2 facingDirection;
    float viewDistance = 0.0f;
};

struct DebugViewModel
{
    Vector2 cameraPosition;
    std::string gameplayStateText;
    std::string missionStateText;
    int enemyCount = 0;
    int updatedEnemyCount = 0;
    int itemCount = 0;
    int bombCount = 0;
    int defeatedEnemyCount = 0;
    float elapsedSeconds = 0.0f;
    std::vector<DebugPointView> points;
    std::vector<DebugRectView> collisionRects;
    std::vector<EnemyVisionView> enemyVisions;
};

struct DebugDisplaySettings
{
    bool showOverlay = true;
    bool showCoordinates = true;
    bool showCollisionBounds = false;
    bool showControlHelp = true;
};
