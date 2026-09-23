#include "WorldRenderer.h"
#include "../Config/GameConfig.h"
#include "../Enemy/EnemyManager.h"
#include "../Game/Gameplay.h"
#include <DxLib.h>

namespace
{
    Vector2 ToScreen(const Gameplay& gameplay, const Vector2& position)
    {
        return gameplay.GetCamera().WorldToScreen(position);
    }

    void DrawWorldRect(const Gameplay& gameplay,const Rect& rect,int color,bool filled)
    {
        const Vector2 screen = ToScreen(gameplay, { rect.x, rect.y });
        DrawBox(static_cast<int>(screen.x),static_cast<int>(screen.y),static_cast<int>(screen.x + rect.width),static_cast<int>(screen.y + rect.height),color,filled ? TRUE : FALSE);
    }
}

void WorldRenderer::Draw(const Gameplay& gameplay) const
{
    DrawBox(0,0,GameConfig::ScreenWidth,GameConfig::ScreenHeight,GetColor(24, 34, 38),TRUE);

    DrawField(gameplay);
    DrawItems(gameplay);
    DrawBombs(gameplay);
    DrawEnemies(gameplay);
    DrawPlayer(gameplay);
}

void WorldRenderer::DrawField(const Gameplay& gameplay) const
{
    const Field& field = gameplay.GetField();
    const Vector2 fieldTopLeft = ToScreen(gameplay, {});

    DrawBox(static_cast<int>(fieldTopLeft.x),static_cast<int>(fieldTopLeft.y),static_cast<int>(fieldTopLeft.x + field.GetWidth()),static_cast<int>(fieldTopLeft.y + field.GetHeight()),GetColor(50, 65, 58),FALSE);

    if (!field.IsBreakableWallDestroyed())
    {
        DrawWorldRect(gameplay,field.GetBreakableWallBounds(),GetColor(120, 80, 55),true);
    }

    DrawWorldRect(gameplay,field.GetMissionTargetBounds(),GetColor(150, 60, 180),false);
    DrawWorldRect(gameplay,field.GetExtractionBounds(),GetColor(30, 180, 200),false);
}

void WorldRenderer::DrawItems(const Gameplay& gameplay) const
{
    for (const WorldItem& item : gameplay.GetItemManager().GetItems())
    {
        const Vector2 screen = ToScreen(gameplay, item.position);
        DrawCircle(static_cast<int>(screen.x),static_cast<int>(screen.y),9,GetColor(230, 210, 70),TRUE);
    }
}

void WorldRenderer::DrawBombs(const Gameplay& gameplay) const
{
    for (const BombEntity& bomb : gameplay.GetGadgetManager().GetBombs())
    {
        const Vector2 screen = ToScreen(gameplay, bomb.position);
        DrawCircle(static_cast<int>(screen.x),static_cast<int>(screen.y),10,GetColor(20, 20, 20),TRUE);
    }
}

void WorldRenderer::DrawEnemies(const Gameplay& gameplay) const
{
    constexpr float ViewDistance = 280.0f;
    constexpr float HalfAngleCosine = 0.7071067f;

    for (const Enemy& enemy : gameplay.GetEnemyManager().GetEnemies())
    {
        const Vector2 enemyScreen = ToScreen(gameplay, enemy.GetPosition());
        const Vector2 facing = enemy.GetFacingDirection();

        const Vector2 leftDirection = {facing.x * HalfAngleCosine - facing.y * HalfAngleCosine,facing.x * HalfAngleCosine + facing.y * HalfAngleCosine};
        const Vector2 rightDirection = {facing.x * HalfAngleCosine + facing.y * HalfAngleCosine,-facing.x * HalfAngleCosine + facing.y * HalfAngleCosine};

        const Vector2 leftEnd = ToScreen(gameplay,enemy.GetPosition() + leftDirection * ViewDistance);
        const Vector2 rightEnd = ToScreen(gameplay,enemy.GetPosition() + rightDirection * ViewDistance);

        DrawLine(static_cast<int>(enemyScreen.x),static_cast<int>(enemyScreen.y),static_cast<int>(leftEnd.x),static_cast<int>(leftEnd.y),GetColor(120, 100, 50));
        DrawLine(static_cast<int>(enemyScreen.x),static_cast<int>(enemyScreen.y),static_cast<int>(rightEnd.x),static_cast<int>(rightEnd.y),GetColor(120, 100, 50));

        int enemyColor = GetColor(200, 55, 55);
        if (enemy.GetState() == EnemyBehaviorState::Suspicious)
        {
            enemyColor = GetColor(255, 220, 40);
        }
        else if (enemy.GetState() == EnemyBehaviorState::Alert)
        {
            enemyColor = GetColor(255, 130, 20);
        }
        else if (enemy.GetState() == EnemyBehaviorState::Chase)
        {
            enemyColor = GetColor(255, 20, 20);
        }

        DrawCircle(static_cast<int>(enemyScreen.x),static_cast<int>(enemyScreen.y),16,enemyColor,TRUE);
    }
}

void WorldRenderer::DrawPlayer(const Gameplay& gameplay) const
{
    const Vector2 screen = ToScreen(gameplay,gameplay.GetPlayer().GetPosition());

    DrawCircle(static_cast<int>(screen.x),static_cast<int>(screen.y),14,GetColor(80, 180, 255),TRUE);
}
