#include "Player.h"
#include "TileMap.h"
#include "CollisionManager.h"
#include "EnemyManager.h"

Player::Player()
	: Entity()
	, Collidable()
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mHealth(100)
	, mRemoveCollider(false)
	, mCurrentAnim(nullptr)
	, mAnimState(AnimState::IdleRight)
	, mFacingRight(true)
	, mFacingDirection(X::Math::Vector2::XAxis())
{
}

Player::~Player()
{
}

void Player::Load()
{
	mImageId = X::LoadTexture("Walk3_Right.png");
	mHealth = 100;
	mFacingDirection = X::Math::Vector2::XAxis();

	const Tile* safeTile = TileMap::Get()->GetFirstWalkableTile();
	mPosition = safeTile->GetPosition();

	float halfWidth = X::GetSpriteWidth(mImageId) * 0.5f;
	float halfHeight = X::GetSpriteHeight(mImageId) * 0.5f;
	mPlayerRect.left = -halfWidth;
	mPlayerRect.right = halfWidth;
	mPlayerRect.top = -halfHeight;
	mPlayerRect.bottom = halfHeight;

	// Load Idle Animations
	std::vector<std::string> idleRightFrames =
	{
		"IdleRight01.png",
		"IdleRight02.png",
		"IdleRight03.png",
		"IdleRight04.png",
		"IdleRight05.png",
		"IdleRight06.png",
		"IdleRight07.png",
		"IdleRight08.png",
		"IdleRight09.png",
		"IdleRight10.png",
		"IdleRight11.png",
		"IdleRight12.png"
	};
	std::vector<std::string> idleLeftFrames =
	{
		"IdleLeft01.png",
		"IdleLeft02.png",
		"IdleLeft03.png",
		"IdleLeft04.png",
		"IdleLeft05.png",
		"IdleLeft06.png",
		"IdleLeft07.png",
		"IdleLeft08.png",
		"IdleLeft09.png",
		"IdleLeft10.png",
		"IdleLeft11.png",
		"IdleLeft12.png"
	};
	std::vector<std::string> idleUpFrames =
	{
		"IdleUp01.png",
		"IdleUp02.png",
		"IdleUp03.png",
		"IdleUp04.png"
	};
	std::vector<std::string> idleDownFrames =
	{
		"IdleDown01.png",
		"IdleDown02.png",
		"IdleDown03.png",
		"IdleDown04.png",
		"IdleDown05.png",
		"IdleDown06.png",
		"IdleDown07.png",
		"IdleDown08.png",
		"IdleDown09.png",
		"IdleDown10.png",
		"IdleDown11.png",
		"IdleDown12.png"
	};

	// Load Walking Animations
	std::vector<std::string> walkRightFrames =
	{
		"WalkRight01.png",
		"WalkRight02.png",
		"WalkRight03.png",
		"WalkRight04.png",
		"WalkRight05.png",
		"WalkRight06.png"
	};
	std::vector<std::string> walkLeftFrames =
	{
		"WalkLeft01.png",
		"WalkLeft02.png",
		"WalkLeft03.png",
		"WalkLeft04.png",
		"WalkLeft05.png",
		"WalkLeft06.png"
	};
	std::vector<std::string> walkUpFrames =
	{
		"WalkUp01.png",
		"WalkUp02.png",
		"WalkUp03.png",
		"WalkUp04.png",
		"WalkUp05.png",
		"WalkUp06.png"
	};
	std::vector<std::string> walkDownFrames =
	{
		"WalkDown01.png",
		"WalkDown02.png",
		"WalkDown03.png",
		"WalkDown04.png",
		"WalkDown05.png",
		"WalkDown06.png"
	};
	std::vector<std::string> attackRightFrames =
	{
		"AttackRight01.png",
		"AttackRight02.png",
		"AttackRight03.png",
		"AttackRight04.png",
		"AttackRight05.png"
	};

	std::vector<std::string> attackLeftFrames =
	{
		"AttackLeft01.png",
		"AttackLeft02.png",
		"AttackLeft03.png",
		"AttackLeft04.png",
		"AttackLeft05.png"
	};
	std::vector<std::string> attackUpFrames =
	{
		"AttackUp01.png",
		"AttackUp02.png",
		"AttackUp03.png",
		"AttackUp04.png",
		"AttackUp05.png"
	};
	std::vector<std::string> attackDownFrames =
	{
		"AttackDown01.png",
		"AttackDown02.png",
		"AttackDown03.png",
		"AttackDown04.png",
		"AttackDown05.png"
	};

	float idleFrameRate = 0.2f;
	float walkFrameRate = 0.1f;
	float attackFrameRate = 0.1f;

	// Idle Animations
	mIdleRight.Load(idleRightFrames, mPosition, 0.0f, 1.0f, idleFrameRate, true);
	mIdleLeft.Load(idleLeftFrames, mPosition, 0.0f, 1.0f, idleFrameRate, true);
	mIdleUp.Load(idleUpFrames, mPosition, 0.0f, 1.0f, idleFrameRate, true);
	mIdleDown.Load(idleDownFrames, mPosition, 0.0f, 1.0f, idleFrameRate, true);

	// Walk Animations
	mWalkRight.Load(walkRightFrames, mPosition, 0.0f, 1.0f, walkFrameRate, true);
	mWalkLeft.Load(walkLeftFrames, mPosition, 0.0f, 1.0f, walkFrameRate, true);
	mWalkUp.Load(walkUpFrames, mPosition, 0.0f, 1.0f, walkFrameRate, true);
	mWalkDown.Load(walkDownFrames, mPosition, 0.0f, 1.0f, walkFrameRate, true);

	mCurrentAnim = &mIdleRight;
	mAnimState = AnimState::IdleRight;
	mFacingRight = true;

	// Collider Stuff
	SetRect(mPlayerRect);
	SetCollidableFilter(ET_PLAYER | ET_PICKUP);
	mRemoveCollider = false;
	CollisionManager::Get()->AddCollidable(this);
}

void Player::SetAnimState(AnimState newState)
{
	if (mAnimState != newState)
	{
		mAnimState = newState;
		switch (mAnimState)
		{
		case AnimState::WalkRight:
			mCurrentAnim = &mWalkRight;
			break;
		case AnimState::WalkLeft:
			mCurrentAnim = &mWalkLeft;
			break;
		case AnimState::WalkUp:
			mCurrentAnim = &mWalkUp;
			break;
		case AnimState::WalkDown:
			mCurrentAnim = &mWalkDown;
			break;
		case AnimState::IdleRight:
			mCurrentAnim = &mWalkRight;
			mFacingRight = true;
			break;
		case AnimState::IdleLeft:
			mCurrentAnim = &mWalkLeft;
			mFacingRight = false;
			break;
		default:
			break;
		}
		mCurrentAnim->SetActive(mPosition, true);
	}
}

void Player::Update(float deltaTime)
{
	if (mHealth <= 0)
	{
		if (mRemoveCollider)
		{
			CollisionManager::Get()->RemoveCollidable(this);
			mRemoveCollider = false;
		}
		return;
	}

	const float speed = 200.0f;
	X::Math::Vector2 direction = X::Math::Vector2::Zero();
	X::Math::Vector2 displacement = X::Math::Vector2::Zero();
	bool isMoving = false;

	if (X::IsKeyDown(X::Keys::W))
	{
		direction.y = -1.0f;
	}
	else if (X::IsKeyDown(X::Keys::S))
	{
		direction.y = 1.0f;
	}
	if (X::IsKeyDown(X::Keys::A))
	{
		direction.x = -1.0f;
	}
	else if (X::IsKeyDown(X::Keys::D))
	{
		direction.x = 1.0f;
	}
	if (X::Math::MagnitudeSqr(direction) > 0.0f)
	{
		isMoving = true;
		direction = X::Math::Normalize(direction);
		mFacingDirection = direction;
		displacement = direction * speed * deltaTime;
		X::Math::Vector2 maxDisplacement = displacement;
		X::Math::Rect currentRect = mPlayerRect;
		currentRect.min += mPosition;
		currentRect.max += mPosition;
		if (TileMap::Get()->HasCollision(currentRect, maxDisplacement, displacement))
		{
			// play hit wall sound
			// play particle effect
			XLOG("Hit Wall!");
			mPosition += displacement;
		}
		else
		{
			mPosition += displacement;
		}

		currentRect = mPlayerRect;
		currentRect.min += mPosition;
		currentRect.max += mPosition;
		SetRect(currentRect);

		// Update Animation State
		if (direction.x > 0.0f)
		{
			SetAnimState(AnimState::WalkRight);
		}
		else if (direction.x < 0.0f)
		{
			SetAnimState(AnimState::WalkLeft);
		}
		else if (direction.y < 0.0f)
		{
			SetAnimState(AnimState::WalkUp);
		}
		else if (direction.y > 0.0f)
		{
			SetAnimState(AnimState::WalkDown);
		}
	}
	else
	{
		// Idle State
		if (mFacingRight)
		{
			SetAnimState(AnimState::IdleRight);
		}
		else
		{
			SetAnimState(AnimState::IdleLeft);
		}
	}

	if (X::IsKeyPressed(X::Keys::F))
	{
		PerformAttack();
	}

	// Update current animation
	if (mCurrentAnim && isMoving)
	{
		mCurrentAnim->Update(deltaTime);
	}
}

void Player::Render()
{
	if (mHealth > 0 && mCurrentAnim)
	{
		mCurrentAnim->SetPosition(mPosition);
		mCurrentAnim->Render();
	}
}

void Player::Unload()
{
	mIdleRight.Unload();
	mIdleLeft.Unload();
	mIdleUp.Unload();
	mIdleDown.Unload();
	mWalkRight.Unload();
	mWalkLeft.Unload();
	mWalkUp.Unload();
	mWalkDown.Unload();
}

int Player::GetType() const
{
	return ET_PLAYER;
}

void Player::OnCollision(Collidable* collidable)
{
	// DONT REMOVE COLLIDABLES DURING THIS FUNCTION
	if (mHealth <= 0)
	{
		return;
	}

	if (collidable->GetType() == ET_ENEMY)
	{
		mHealth -= 10;
	}
	else if (collidable->GetType() == ET_PICKUP)
	{
		mHealth += 20;
	}
	mHealth = X::Math::Clamp(mHealth, 0, 100);
	if (mHealth <= 0)
	{
		mRemoveCollider = true;
	}
}

const X::Math::Vector2& Player::GetPosition() const
{
	return mPosition;
}

void Player::SetPosition(const X::Math::Vector2& position)
{
	mPosition = position;
}

void Player::SetVelocity(const X::Math::Vector2& velocity)
{
	mVelocity = velocity;
}

const X::Math::Vector2& Player::GetVelocity() const
{
	return mVelocity;
}

int Player::GetHealth() const
{
	return mHealth;
}

bool Player::IsDead() const
{
	return mHealth <= 0;
}

void Player::PerformAttack()
{
	const float attackRange = 20.0f;
	const float attackWidth = 25.0f;

	X::Math::Vector2 attackDirection = mFacingDirection;
	if (X::Math::MagnitudeSqr(attackDirection) <= 0.0f)
	{
		attackDirection = mFacingRight ? X::Math::Vector2::XAxis() : -X::Math::Vector2::XAxis();
	}

	attackDirection = X::Math::Normalize(attackDirection);
	X::Math::Vector2 attackCenter = mPosition + attackDirection * attackRange;

	X::Math::Rect attackRect;
	attackRect.left = attackCenter.x - attackWidth * 0.5f;
	attackRect.right = attackCenter.x + attackWidth * 0.5f;
	attackRect.top = attackCenter.y - attackWidth * 0.5f;
	attackRect.bottom = attackCenter.y + attackWidth * 0.5f;

	EnemyManager::Get()->ApplyDamageInArea(attackRect, 10);
}