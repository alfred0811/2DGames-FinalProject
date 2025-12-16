#include <XEngine.h>
#include "GameController.h"
#include "StartState.h"
#include "RunGameState.h"
#include "EndState.h"

State gActiveState = State::Start;
GameState* gCurrentGameState = nullptr;
std::map<State, GameState*> gGameStates;

// Game Setup
void GameInit()
{
	GameController::Get()->Load();
}

bool GameUpdate(float deltaTime)
{
	GameController::Get()->Update(deltaTime);
	GameController::Get()->Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	GameController::Get()->Unload();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");

	GameInit();

	X::Run(GameUpdate);

	GameCleanup();

	return 0;
}