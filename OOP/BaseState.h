#pragma once

struct GameInfo
{
	int diff;
	int enemyNum;
};

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

	static GameInfo& GetInfo() { return info; }
};

