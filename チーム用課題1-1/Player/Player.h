#pragma once

#include "../Core/Math/Rect.h"
#include "../Input/PlayerCommand.h"

enum class PlayerActionState
{
    Idle,
    Move,
    Attack,
    Dodge,
    Damage,
    Dead
};

class Player
{
public:
    void Update(const PlayerCommand& command, float deltaSeconds);
    void ApplyDamage(int damage);
    void StopAt(const Vector2& position);

    Vector2 GetPosition() const;
    Vector2 GetFacingDirection() const;
    Rect GetCollisionBounds() const;
    Vector2 GetAttackCenter() const;
    float GetAttackRadius() const;
    int GetHp() const;
    int GetMaxHp() const;
    PlayerActionState GetState() const;
    bool IsAttackActive() const;
    bool IsDead() const;

private:
    static constexpr float MoveSpeed = 190.0f;
    static constexpr float DodgeSpeed = 380.0f;
    static constexpr float CollisionRadius = 14.0f;
    static constexpr float AttackRadius = 28.0f;
    static constexpr float AttackOffset = 28.0f;
    static constexpr float AttackDuration = 0.18f;
    static constexpr float DodgeDuration = 0.22f;
    static constexpr float DodgeInvincibilityDuration = 0.30f;
    static constexpr float DamageInvincibilityDuration = 1.0f;
    static constexpr int MaximumHp = 5;

    Vector2 position_ = { 140.0f, 360.0f };
    Vector2 facingDirection_ = { 1.0f, 0.0f };
    PlayerActionState state_ = PlayerActionState::Idle;
    int hp_ = MaximumHp;
    float actionTimer_ = 0.0f;
    float invincibilityTimer_ = 0.0f;
};
