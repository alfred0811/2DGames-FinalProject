#include "AnimSeperateImages.h"

AnimSeperateImages::AnimSeperateImages()
	: Entity()
	, mSpritePaths()
	, mSpriteIds()
	, mPosition(0.0f, 0.0f)
	, mRotation(0.0f)
	, mScale(1.0f)
	, mFrameRate(0.0f)
	, mCurrentFrameTime(0.0f)
	, mCurrentIndex(0)
	, mIsLooping(false)
	, mAnimationEnabled(true)
{
}

AnimSeperateImages::~AnimSeperateImages()
{
}

void AnimSeperateImages::Load()
{
}

void AnimSeperateImages::Load(std::vector<std::string> spritePaths,
	X::Math::Vector2 position,
	float rotation,
	float scale,
	float frameRate,
	bool isLooping)
{
	mSpritePaths = spritePaths;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	mFrameRate = frameRate;
	mIsLooping = isLooping;
	mCurrentIndex = 0;

	// Pre-load all textures
	mSpriteIds.clear();
	for (const auto& path : mSpritePaths)
	{
		mSpriteIds.push_back(X::LoadTexture(path.c_str()));
	}
}

void AnimSeperateImages::Update(float deltaTime)
{
	if (IsActive())
	{
		mCurrentFrameTime += deltaTime;

		while (mCurrentFrameTime > mFrameRate)
		{
			mCurrentFrameTime -= mFrameRate;
			++mCurrentIndex;
		}

		if (mCurrentIndex >= mSpritePaths.size())
		{
			if (mIsLooping)
			{
				while (mCurrentIndex >= mSpritePaths.size())
				{
					mCurrentIndex -= mSpritePaths.size();
				}
			}
			else
			{
				mCurrentIndex = -1;
			}
		}
	}
}

void AnimSeperateImages::Render()
{
	if (IsActive())
	{
		X::DrawSprite(X::LoadTexture(mSpritePaths[mCurrentIndex].c_str()), mPosition, mRotation, X::Pivot::Center, X::Flip::None);
	}
}

void AnimSeperateImages::Render(X::Math::Vector2& position, float rotation, X::Flip flip)
{
	mPosition = position;
	mRotation = rotation;

	if (IsActive())
	{
		X::DrawSprite(X::LoadTexture(mSpritePaths[mCurrentIndex].c_str()), mPosition, mRotation, X::Pivot::Center, flip);
	}
}

void AnimSeperateImages::Unload()
{
}

void  AnimSeperateImages::SetActive(const X::Math::Vector2& position, bool loop)
{
	mPosition = position;
	mIsLooping = loop;
	mCurrentIndex = 0;
	mCurrentFrameTime = 0.0f;
}
bool  AnimSeperateImages::IsActive() const
{
	return (mIsLooping || mCurrentIndex >= 0) && mAnimationEnabled;
}

bool AnimSeperateImages::GetAnimationEnabled() const
{
	return mAnimationEnabled;
}

void AnimSeperateImages::SetAnimationEnabled(bool enabled)
{
	mAnimationEnabled = enabled;
}

void AnimSeperateImages::SetPositionAndRotation(X::Math::Vector2& position, float rotation)
{
	mPosition = position;
	mRotation = rotation;
}

void AnimSeperateImages::SetPosition(X::Math::Vector2& position)
{
	mPosition = position;
}

void AnimSeperateImages::SetRotation(float rotation)
{
	mRotation = rotation;
}