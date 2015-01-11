#pragma once
#include "BaseState.h"
class GameState :
	public BaseState
{
public:
	GameState();
	~GameState();

	void Input();
	void Update(int _frame);
	void Render();

	void Enter();
	void Exit();
};

