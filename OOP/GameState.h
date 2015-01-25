#pragma once
#include "BaseState.h"
#include "Cell.h"

class BaseObject;



/** @brief GameState class control actual gameplay.
*	@author Junshu Chen
*	@date Jan 2015
*/
class GameState : public BaseState
{
private:
	static DList<BaseObject*> gameObjects;
	vector<BaseObject*> readInObjects; //An array of Objects read from file images.txt
	const int MAXBOSS = 1;
	int boss = 0;
	int enemyCount = 0;
	int waves = 1;
	const int MAXWAVES = 10;
	int numofStars;
	Cell<>* stars;
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
	static DList<BaseObject*>& GetObjects() { return gameObjects; }

	/** Load readInObjects Array  from file "images.txt".
	*/
	void ReadObFromFile(); //

	/** Generate stars on screen
	*/
	void GenerateStars();
};

