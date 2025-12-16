#include <XEngine.h>
#include "RunGameState.h"
#include "GameController.h"

RunGameState::RunGameState()
	: GameState(State::RunGame)
	, mGameController(GameController::Get())
	, mElapsedTime(0.0f)
{
}

RunGameState::~RunGameState()
{
}

void RunGameState::Load()
{
	mElapsedTime = 0.0f;
	mGameController->Load();
}

State RunGameState::Update(float deltaTime)
{
	mElapsedTime += deltaTime;
	mGameController->Update(deltaTime);

	if (mGameController->IsGameOver())
	{
		return State::End;
	}
	return State::RunGame;
}

void RunGameState::Render()
{
	mGameController->Render();

	const float textSize = 24.0f;
	char hud[64];
	sprintf_s(hud, "Health: %d", mGameController->GetPlayerHealth());
	X::DrawScreenText(hud, 20.0f, 20.0f, textSize, X::Colors::White);
}

void RunGameState::Unload()
{
	mGameController->Unload();
}

int RunGameState::GetFinalScore() const
{
	return static_cast<int>(mElapsedTime);
}