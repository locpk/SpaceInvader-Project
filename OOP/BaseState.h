#pragma once

/**
* GameInfo struct to passing game setting between states.
*/
struct GameInfo
{
	int diff;
	int enemyNum;
};

/**
*	A abstract Base Class for states.
*	@author Junshu Chen
*	@date Jan 2015
*/
class BaseState
{
private:
	static GameInfo info;
public:
	BaseState();
	virtual ~BaseState();

	virtual void Input() = 0;
	virtual void Update(int _frame) = 0;
	virtual void Render() = 0;

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	/**
	*Getinfo return Game setting info.
	*@return a reference to BaseState private member info.
	*/
	static GameInfo& GetInfo() { return info; }
};

