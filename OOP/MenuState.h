#pragma once
#include "BaseState.h"

/** @brief MenuState class control menu layout m.
*	@author Junshu Chen
*	@date Jan 2015
*/
class MenuState : public BaseState
{
private:
	int menuNum;
	string menuStrings[4];
	bool buttonPressed = false; 
	string menuArt;

public:
	/** Constructor
	*	Layout Menu and read the menu art from MenuART.txt.
	*/
	MenuState();

	/** Destructor.
	*/
	~MenuState();

	/** Handle user input enable user to select and enter different menu items.
	*/
	void Input();

	/** Update keyboard buffer
	*/
	void Update(int _frame);

	/** Render the menu
	*/
	void Render();

	/** flush keys when entering menu state
	*/
	void Enter();

	/** flush keys when exiting menu state
	*/
	void Exit();
};

