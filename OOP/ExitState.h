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
};

