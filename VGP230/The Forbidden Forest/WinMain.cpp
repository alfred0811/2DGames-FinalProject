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
	gGameStates[State::Start] = new StartState();
	gGameStates[State::RunGame] = new RunGameState();
	gGameStates[State::End] = new EndState();

	gCurrentGameState = gGameStates[gActiveState];
	gCurrentGameState->Load();
}

bool GameUpdate(float deltaTime)
{
	State nextState = gCurrentGameState->Update(deltaTime);
	gCurrentGameState->Render();

	if (nextState != gActiveState)
	{
		if (nextState == State::End)
		{
			RunGameState* runState = dynamic_cast<RunGameState*>(gCurrentGameState);
			EndState* endState = dynamic_cast<EndState*>(gGameStates[State::End]);
			if (runState != nullptr && endState != nullptr)
			{
				endState->SetFinalScore(runState->GetFinalScore());
			}
		}

		gCurrentGameState->Unload();
		gActiveState = nextState;
		gCurrentGameState = gGameStates[gActiveState];
		gCurrentGameState->Load();
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	if (gCurrentGameState != nullptr)
	{
		gCurrentGameState->Unload();
	}

	for (auto& [state, gameState] : gGameStates)
	{
		delete gameState;
	}
	gGameStates.clear();
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");

	GameInit();

	X::Run(GameUpdate);

	GameCleanup();

	return 0;
}