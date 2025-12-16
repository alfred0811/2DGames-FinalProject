#pragma once

#include "Entity.h"

class AnimSeperateImages : public Entity
{
public:
    AnimSeperateImages();
    ~AnimSeperateImages();

    void Load() override;
    void Load(std::vector<std::string> spritePaths,
        X::Math::Vector2 position,
        float rotation,
        float scale,
        float frameRate,
        bool isLooping);

    void Update(float deltaTime) override;
    void Render() override;
    void Render(X::Math::Vector2& position, float rotation, X::Flip flip);

    void Unload() override;

    void SetActive(const X::Math::Vector2& position, bool loop = false);
    bool IsActive() const;

    bool GetAnimationEnabled() const;
    void SetAnimationEnabled(bool enabled);

    void SetPositionAndRotation(X::Math::Vector2& position, float rotation);
    void SetPosition(X::Math::Vector2& position);
    void SetRotation(float rotation);

private:
    std::vector<std::string> mSpritePaths;
    std::vector<X::TextureId> mSpriteIds;

    X::Math::Vector2 mPosition;
    float mRotation;
    float mScale;

    float mFrameRate;
    float mCurrentFrameTime;
    int mCurrentIndex;
    bool mIsLooping;
    bool mAnimationEnabled;
};