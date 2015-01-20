#include "stdafx.h"
#include "ExitState.h"
#include "Game.h"


ExitState::ExitState()
{
}


ExitState::~ExitState()
{
}

void ExitState::Enter()
{
	Game::SetPlay(false);
}

void ExitState::Render()
{
	Console::Clear();
	Console::SetCursorPosition(Console::WindowWidth() >> 1, Console::WindowHeight() >> 1);
	cout << "Bye!";
}

void ExitState::Update(int _frame)
{

}
void ExitState::Input()
{

}
void ExitState::Exit()
{

}