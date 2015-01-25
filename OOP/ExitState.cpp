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