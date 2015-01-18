#pragma once
#include "BaseState.h"


class BaseObject;

class GameState :
	public BaseState
{
private:
	static vector<BaseObject*> gameObjects;
public:
	GameState();
	~GameState();

	void Input();
	void Update(int _frame);
	void Render();

	void Enter();
	void Exit();

	static vector<BaseObject*>* GetObjects() { return &gameObjects; }
};

