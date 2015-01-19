#pragma once
#include "BaseState.h"
class MenuState :
	public BaseState
{
private:
	int menuNum;
	string menuStrings[3];

	bool buttonPressed = false;

	string menuArt;

public:
	MenuState();
	~MenuState();

	void Input();
	void Update(int _frame);
	void Render();

	void Enter();
	void Exit();
};

