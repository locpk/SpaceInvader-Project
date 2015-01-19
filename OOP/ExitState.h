#pragma once
#include "BaseState.h"
class ExitState :
	public BaseState
{
public:
	ExitState();
	~ExitState();


	void Enter();
	void Exit();
	void Input();
	void Update(int _iframe);
	void Render();
};

