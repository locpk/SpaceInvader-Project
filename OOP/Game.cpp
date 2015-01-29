#include "stdafx.h"
#include "Game.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "BaseState.h"
#include "GameState.h"
#include "MenuState.h"
#include "OptionState.h"
#include "HighScoreState.h"
#include "ExitState.h"


BaseState* Game::currentState = NULL;
vector<BaseState*> Game::states;
bool Game::play = true;
char Game::cheats = 1;
Game::Game()
{
	System::Console::SetBufferSize(200, 50);
	System::Console::SetWindowSize(200, 50);
	System::Console::EOLWrap(false);
	//Set up the states
	states.push_back(new MenuState());
	states.push_back(new GameState());
	states.push_back(new OptionState());
	states.push_back(new HighScoreState());
	states.push_back(new ExitState());
}


Game::~Game()
{
	int i = 0;
	for (; i < (int)states.size(); i++)
	{
		delete states[i];
	}
}

void Game::Play()
{
	ChangeState(MENU_STATE);

	for (;play && (cheats & ALIVE_FLAG); ++frame)
	{
		Input();
		Update(frame);
		Render();
		Sleep(30);
	}
}

void Game::Input()
{

	currentState->Input();

	/*if (GetAsyncKeyState(VK_ESCAPE))
		play = false;*/


}
void Game::Update(int _frame)
{
	currentState->Update(_frame);
}
void Game::Render()
{
	System::Console::Lock(true);
	System::Console::Clear();
	currentState->Render();
	System::Console::Lock(false);
}


void Game::ChangeState(STATE_TYPES _state)
{
	if (currentState)
		currentState->Exit();

	currentState = states[_state];
	currentState->Enter();
}
