#pragma once
#include "BaseState.h"

struct PlayerInfo;

class HighScoreState : public BaseState
{
private:
	bool buttonPressed = false;
	vector<PlayerInfo> inScores;
public:
	HighScoreState();
	~HighScoreState();

	void Input();
	void Update(int _frame);
	void Render();

	void Enter();
	void Exit();
};

