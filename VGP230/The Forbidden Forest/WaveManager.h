#pragma once

#include "EnemyManager.h"

class WaveManager : public Entity
{
public:
	~WaveManager();
	static WaveManager* Get();

	void Load();
	void Update(float deltaTime);
	void Render();
	void Unload();

	void StartWave();
	bool IsWaveComplete() const;

	int GetCurrentWave() const;
	int GetEnemiesRemaining() const;

private:
	WaveManager();
	static WaveManager* mInstance;

	EnemyManager* mEnemyManager;
};