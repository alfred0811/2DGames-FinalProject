#include "GameController.h"
#include "TileMap.h"
#include "CollisionManager.h"
#include "PickupManager.h"
#include "EnemyManager.h"

GameController* GameController::mInstance = nullptr;

GameController::GameController()
	: Entity()
{
}

GameController::~GameController()
{
}

GameController* GameController::Get()
{
	if (mInstance == nullptr)
	{
		mInstance = new GameController();
	}
	return mInstance;
}

// Entity override
void GameController::Load()
{
	CollisionManager::Get()->Load();
	PickupManager::Get()->Load();
	TileMap::Get()->Load();
	EnemyManager::Get()->Load();
	mPlayer.Load();
	EnemyManager::Get()->SetPlayer(&mPlayer);
}

void GameController::Update(float deltaTime)
{
	TileMap::Get()->Update(deltaTime);
	PickupManager::Get()->Update(deltaTime);
	EnemyManager::Get()->Update(deltaTime);
	mPlayer.Update(deltaTime);

	// do collision
	CollisionManager::Get()->Update(deltaTime);
}

void GameController::Render()
{
	TileMap::Get()->Render();
	PickupManager::Get()->Render();
	EnemyManager::Get()->Render();
	mPlayer.Render();

	// only renders Debug
	CollisionManager::Get()->Render();
}

void GameController::Unload()
{
	TileMap::Get()->Unload();
	PickupManager::Get()->Unload();
	EnemyManager::Get()->Unload();
	mPlayer.Unload();
	CollisionManager::Get()->Unload();
}

bool GameController::IsGameOver() const
{
	return mPlayer.IsDead();
}

int GameController::GetPlayerHealth() const
{
	return mPlayer.GetHealth();
}