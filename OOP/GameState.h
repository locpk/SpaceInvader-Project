#pragma once
#include "BaseState.h"


class BaseObject;

/** @brief GameState class control actual gameplay.
*	@author Junshu Chen
*	@date Jan 2015
*/
class GameState : public BaseState
{
private:
	static vector<BaseObject*> gameObjects;
	vector<BaseObject*> readInObjects; //An array of Objects read from file images.txt
	int enemyCount = 0;
public:
	/** Constructor 
	*	load player Image2D from file "Images.txt"
	*/
	GameState();

	/** Destructor
	*	delete all game objects.
	*/
	~GameState();

	/** call each game object's input function.
	*/
	void Input();

	/** call each game object's update function.
	*	@param _frame global frame count.
	*/
	void Update(int _frame);

	/** call each game object's render function.
	*/
	void Render();

	/** Set up game based on the options player choose, the enemy number and difficulty.
	*/
	void Enter();

	/** Save player's score in t scores.txt and scores.bin and return to main menu.
	*/
	void Exit();

	/** Return a point to gameObject array.
	*	@return the address of the vector array of gameObjects
	*/
	static vector<BaseObject*>* GetObjects() { return &gameObjects; }

	/** Load readInObjects Array  from file "images.txt".
	*/
	void ReadObFromFile(); //

};

