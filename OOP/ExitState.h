#pragma once
#include "BaseState.h"


/** @brief ExitState class exit state.
*
*	@author Junshu Chen
*	@date Jan 2015
*/
class ExitState : public BaseState
{
public:
	ExitState();
	~ExitState();

	/** Enter ExitState and set Game::play to false to terminate the game.
	*/
	void Enter();

	/** Render Exit message on screen.
	*/
	void Render();

	void Update(int _frame);
	void Input();
	void Exit();
};

