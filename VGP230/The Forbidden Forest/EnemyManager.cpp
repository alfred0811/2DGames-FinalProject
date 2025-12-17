#include <XEngine.h>

#include "EnemyManager.h"
#include "TileMap.h"

EnemyManager* EnemyManager::mInstance = nullptr;

EnemyManager::EnemyManager()
	: Entity()
	, mNextAvailableIndex(0)
	, mSpawnTimer(0.0f)
{
}

EnemyManager::~EnemyManager()
{
}

EnemyManager* EnemyManager::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new EnemyManager();
	}
	return mInstance;
}

void EnemyManager::Load()
{
	const int maxEnemies = 100;
	for (int i = 0; i < maxEnemies; ++i)
	{
		Enemy* newEnemy = new Enemy();
		newEnemy->Load();
		mEnemies.push_back(newEnemy);
	}
	mSpawnTimer = 0.0f;
}

void EnemyManager::Update(float deltaTime)
{
	mSpawnTimer -= deltaTime;
	if (mSpawnTimer <= 0.0f)
	{
		SpawnEnemies(1);
		mSpawnTimer = mSpawnInterval;
	}
	for (Enemy* enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}
}

void EnemyManager::Render()
{
	for (Enemy* enemy : mEnemies)
	{
		enemy->Render();
	}
}

void EnemyManager::Unload()
{
	for (Enemy* enemy : mEnemies)
	{
		enemy->Unload();
		delete enemy;
		enemy = nullptr;
	}
	mEnemies.clear();
}

void EnemyManager::SpawnEnemies(int amount)
{
	std::vector<Tile*> walkableTiles;
	TileMap::Get()->ObtainAllWalkableTiles(walkableTiles);
	if (walkableTiles.empty())
	{
		return;
	}
	for (Enemy* enemy : mEnemies)
	{
		if (enemy->IsActive())
		{
			for (int i = 0; i < walkableTiles.size(); ++i)
			{
				if (walkableTiles[i]->HasCollision(enemy->GetRect()))
				{
					if (i < walkableTiles.size() - 1)
					{
						Tile* tmp = walkableTiles[walkableTiles.size() - 1];
						walkableTiles[walkableTiles.size() - 1] = walkableTiles[i];
						walkableTiles[i] = tmp;
					}
					walkableTiles.pop_back();
					break;
				}
			}
		}
	}
	int prevUsedIndex = 0;
	for (int i = 0; i < amount; ++i)
	{
		prevUsedIndex = mNextAvailableIndex - 1;
		if (prevUsedIndex < 0)
		{
			prevUsedIndex = mEnemies.size() - 1;
		}

		while (mNextAvailableIndex != prevUsedIndex)
		{
			Enemy* enemy = mEnemies[mNextAvailableIndex];
			mNextAvailableIndex = (mNextAvailableIndex + 1) % mEnemies.size();
			if (!enemy->IsActive())
			{
				int randIndex = X::Random(0, walkableTiles.size() - 1);
				Tile* randomTile = walkableTiles[randIndex];
				enemy->SetActive(randomTile->GetPosition(), 10);
				if (randIndex < walkableTiles.size() - 1)
				{
					Tile* temp = walkableTiles[walkableTiles.size() - 1];
					walkableTiles[walkableTiles.size() - 1] = walkableTiles[randIndex];
					walkableTiles[randIndex] = temp;
				}
				walkableTiles.pop_back();
				break;
			}
		}
	}
}

void EnemyManager::ApplyDamageInArea(const X::Math::Rect& attackRect, int damage)
{
	for (Enemy* enemy : mEnemies)
	{
		if (enemy->IsActive() && X::Math::Intersect(attackRect, enemy->GetRect()))
		{
			enemy->TakeDamage(damage);
		}
	}
}