#pragma once
#include "BaseState.h"
class OptionState : public BaseState
{
private:
	int menuNum;
	int enemyNum;
	int diff;
	vector<string> menuStrings;

	bool buttonPressed = false;
public:
	OptionState();
	~OptionState();

	void Input();
	void Update(int _frame);
	void Render();

	void Enter();
	void Exit();
};

