#pragma once
#include "BaseState.h"

struct PlayerInfo;

class HighScoreState : public BaseState
{
private:
	int menuNum;
	string menuStrings[6];
	bool buttonPressed = false;
	bool showScore = false;
	vector<PlayerInfo> inScores;
public:
	HighScoreState();
	~HighScoreState();

	void Input();
	void Update(int _frame);
	void Render();

	void Enter();
	void Exit();
	void Read();
	void SaveAs();
};

