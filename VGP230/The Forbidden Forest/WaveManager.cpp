#include "WaveManager.h"

WaveManager* WaveManager::mInstance = nullptr;

WaveManager::WaveManager()
	: Entity()
	, mEnemyManager(nullptr)
{
}

WaveManager::~WaveManager()
{
}

WaveManager* WaveManager::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new WaveManager();
	}
	return mInstance;
}

void WaveManager::Load()
{

}

void WaveManager::Update(float deltaTime)
{

}

void WaveManager::Render()
{

}

void WaveManager::Unload()
{

}

void WaveManager::StartWave()
{
}

bool WaveManager::IsWaveComplete() const
{
	return false;
}

int WaveManager::GetCurrentWave() const
{
	return 0;
}

int WaveManager::GetEnemiesRemaining() const
{
	return 0;
}

