#pragma once

#include "Enemy.h"

class Player;

class EnemyManager : public Entity
{
public:
	~EnemyManager();
	static EnemyManager* Get();

	void Load() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	void SpawnEnemies(int amount);
	void ApplyDamageInArea(const X::Math::Rect& attackRect, int damage);
	void SetPlayer(Player* player);

private:
	EnemyManager();
	static EnemyManager* mInstance;

	std::vector<Enemy*> mEnemies;
	int mNextAvailableIndex;
	float mSpawnTimer;
	const float mSpawnInterval = 1.5f;
	Player* mPlayer = nullptr;
};