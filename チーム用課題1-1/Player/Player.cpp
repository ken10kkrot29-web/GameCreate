#include "Player.h"
#include <algorithm>

void Player::Update(const PlayerCommand& command, float deltaSeconds)
{
    actionTimer_ = (std::max)(0.0f, actionTimer_ - deltaSeconds);
    invincibilityTimer_ = (std::max)(0.0f, invincibilityTimer_ - deltaSeconds);

    if (command.dodgePressed && actionTimer_ <= 0.0f)
    {
        state_ = PlayerActionState::Dodge;
        actionTimer_ = DodgeDuration;
        invincibilityTimer_ = DodgeInvincibilityDuration;
    }
    else if (command.attackPressed && actionTimer_ <= 0.0f)
    {
        state_ = PlayerActionState::Attack;
        actionTimer_ = AttackDuration;
    }
    else if (actionTimer_ <= 0.0f)
    {
        state_ = LengthSquared(command.moveDirection) > 0.0f ? PlayerActionState::Move : PlayerActionState::Idle;
    }

    if (LengthSquared(command.moveDirection) > 0.0f)
    {
        facingDirection_ = command.moveDirection;
    }

    const float speed = state_ == PlayerActionState::Dodge ? DodgeSpeed : MoveSpeed;

    position_ = position_ + command.moveDirection * (speed * deltaSeconds);
}

void Player::ApplyDamage(int damage)
{
    if (invincibilityTimer_ > 0.0f || state_ == PlayerActionState::Dead)
    {
        return;
    }

    hp_ = (std::max)(0, hp_ - damage);
    invincibilityTimer_ = DamageInvincibilityDuration;
    state_ = hp_ == 0 ? PlayerActionState::Dead : PlayerActionState::Damage;
}

void Player::StopAt(const Vector2& position)
{
    position_ = position;
}

Vector2 Player::GetPosition() const { return position_; }
Vector2 Player::GetFacingDirection() const { return facingDirection_; }
int Player::GetHp() const { return hp_; }
int Player::GetMaxHp() const { return MaximumHp; }
PlayerActionState Player::GetState() const { return state_; }
bool Player::IsAttackActive() const { return state_ == PlayerActionState::Attack && actionTimer_ > 0.0f; }
bool Player::IsDead() const { return state_ == PlayerActionState::Dead; }
float Player::GetAttackRadius() const { return AttackRadius; }

Rect Player::GetCollisionBounds() const
{
    return
    {
        position_.x - CollisionRadius,
        position_.y - CollisionRadius,
        CollisionRadius * 2.0f,
        CollisionRadius * 2.0f
    };
}

Vector2 Player::GetAttackCenter() const
{
    return position_ + facingDirection_ * AttackOffset;
}
