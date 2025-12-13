#include "Boss.h"

Boss::Boss()
	: Entity()
	, Collidable()
	, mImageId(0)
	, mPosition(0.0f, 0.0f)
	, mCenterPoint(0.0f, 0.0f)
	, mTargetPoint(0.0f, 0.0f)
	, mTargetPointUpdate(0.0f)
	, mHealth(0)
	, mRemoveCollider(false)
	, mEnemyRect(0, 0, 0, 0)
{
}

Boss::~Boss()
{
}

void Boss::Load()
{
}

void Boss::Update(float deltaTime)
{
}

void Boss::Render()
{
}

void Boss::Unload()
{
}

int Boss::GetType() const
{
	return 0;
}

const X::Math::Vector2& Boss::GetPosition() const
{
	
}

void Boss::OnCollision(Collidable* collidable)
{
}

bool Boss::IsActive() const
{
	return mHealth > 0;
}

void Boss::SetActive(const X::Math::Vector2& position, int health)
{
	mPosition = position;
	mHealth = health;
}
