#pragma once

#include <string>

struct HudViewModel
{
    int playerHp = 0;
    int playerMaxHp = 0;
    int scrapCount = 0;
    int bombCount = 0;
    int enemyCount = 0;
    int updatedEnemyCount = 0;
    int collisionCandidateCount = 0;
    std::string missionText;
};
