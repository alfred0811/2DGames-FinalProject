#pragma once

#include "GameState.h"

class GameController;

class RunGameState : public GameState
{
public:
	RunGameState();
	~RunGameState() override;

	void Load() override;
	State Update(float deltaTime) override;
	void Render() override;
	void Unload() override;

	int GetFinalScore() const;

private:
	GameController* mGameController;
	float mElapsedTime;
};