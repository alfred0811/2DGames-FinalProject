#pragma once

#include "Entity.h"
#include "Collidable.h"
#include "AnimSeperateImages.h"

class Player : public Entity, public Collidable
{
public:
	Player();
	~Player();

	// Entity override
	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	// Collidable override
	int GetType() const override;
	void OnCollision(Collidable* collidable) override;
	const X::Math::Vector2& GetPosition() const override;

	// Player functions
	void SetPosition(const X::Math::Vector2& position);
	void SetVelocity(const X::Math::Vector2& velocity);
	const X::Math::Vector2& GetVelocity() const;
	int GetHealth() const;
	bool IsDead() const;

private:
	enum class AnimState
	{
		IdleRight,
		IdleLeft,
		IdleUp,
		IdleDown,
		WalkRight,
		WalkLeft,
		WalkUp,
		WalkDown,
		AttackRight,
		AttackLeft,
		AttackUp,
		AttackDown
	};

	enum class FacingDirection
	{
		Right,
		Left,
		Up,
		Down
	};

	void SetAnimState(AnimState newState);
	void Attack();
	void UpdateAttack(float deltaTime);
	X::Math::Rect GetAttackHitbox() const;

	X::TextureId mImageId;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;
	X::Math::Rect mPlayerRect;
	int mHealth;
	bool mRemoveCollider;

	// Animation members
	AnimSeperateImages mIdleRight;
	AnimSeperateImages mIdleLeft;
	AnimSeperateImages mIdleUp;
	AnimSeperateImages mIdleDown;
	AnimSeperateImages mWalkRight;
	AnimSeperateImages mWalkLeft;
	AnimSeperateImages mWalkUp;
	AnimSeperateImages mWalkDown;
	AnimSeperateImages* mCurrentAnim;
	AnimState mAnimState;
	bool mFacingRight;
	X::Math::Vector2 mFacingDirection;

	void PerformAttack();
};