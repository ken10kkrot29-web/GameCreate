#include "GameHud.h"
#include <DxLib.h>

void GameHud::Draw(const HudViewModel& viewModel) const
{
    const int white = GetColor(255, 255, 255);

    DrawFormatString(20,15,white,"HP %d / %d    Scrap %d    Bomb %d",viewModel.playerHp,viewModel.playerMaxHp,viewModel.scrapCount,viewModel.bombCount);

    DrawString(20,45,viewModel.missionText.c_str(),white);

    DrawFormatString(20,75,GetColor(180, 220, 180),"Enemies %d    Updated %d    Collision candidates %d",viewModel.enemyCount,viewModel.updatedEnemyCount,viewModel.collisionCandidateCount);
}
