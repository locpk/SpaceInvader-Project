#pragma once
#include "BaseState.h"

/** @brief OptionState class.
*	@author Junshu Chen
*	@date Jan 2015
*/
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

	/**Enable Player to switch between menu items.
	*/
	void Input();
	void Update(int _frame);

	/**
	* Render option Menu.
	*/
	void Render();

	void Enter();
	void Exit();
};

