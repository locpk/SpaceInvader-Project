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
void ExitState::Exit()
{

}

void ExitState::Input()
{

}
void ExitState::Update(int _iframe)
{

}
void ExitState::Render()
{
	Console::Clear();
	Console::SetCursorPosition(Console::WindowWidth() >> 1, Console::WindowHeight() >> 1);
	cout << "Bye!";
}