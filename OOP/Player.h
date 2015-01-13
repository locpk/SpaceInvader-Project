#pragma once
#include "BaseObject.h"
class Player :
	public BaseObject
{
private:
	char* name;
	int score, diff;
public:
	Player();
	Player(const char* const _name, int _score, int _diff, 
		const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const short _x = 0, const short _y = 0);
	Player(const Player& _obj);
	Player& operator=(const Player& _obj);
	~Player();

	//accessors
	char* GetName() const { return name; }
	int GetScore() const { return score; }
	int GetDiff() const { return diff; }

	//mutators
	void SetName(const char* const _name) { delete[] name; name = _strdup(_name); }
	void SetScore(const int _score) { score = _score; }
	void SetDiff(const int _diff)	{ diff = _diff; }

	void Input();
	void Update(int _frame);
	void Render();
	
};

