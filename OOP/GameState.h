#pragma once
#include "BaseState.h"


class BaseObject;

class GameState :
	public BaseState
{
private:
	int numofRI = 0; //number of read in objects
	BaseObject* readinObjects;
	static BaseObject* gameObjects[NUMOFGO];
public:
	GameState();
	~GameState();

	void Input();
	void Update(int _frame);
	void Render();

	void Enter();
	void Exit();

	static BaseObject** GetObjects() { return gameObjects; }
};

