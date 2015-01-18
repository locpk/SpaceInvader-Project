#pragma once
#include "BaseObject.h"

struct PlayerInfo
{
	char buffer[32];
	int score;
	int diff;
};

class Player :
	public BaseObject
{
private:
	string name;
	int score, diff;
	int hp = 100;
	bool buttonPressed = false;
	int numofHM = 10; // number of Homing Missiles
	int numofRK = 5;  // number of Rockets
	bool launched = false; // indicates is a rocket has been launched

public:
	Player();
	Player(const char* const _name, int _score, int _diff, 
		const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const short _x = 0, const short _y = 0);
	Player(const Player& _obj);
	Player& operator=(const Player& _obj);
	~Player();

	//accessors
	const char* const GetName() const { return name.c_str(); }
	int GetScore() const { return score; }
	int GetDiff() const { return diff; }
	int GetNumofHM()const { return numofHM; }
	int GetNumofRK()const { return numofRK; }
	bool GetLaunched() const{ return launched; }
	int GetHP() const { return hp; }

	//mutators
	void SetName(const char* const _name) { name = _name; }
	void SetScore(const int _score) { score = _score; }
	void SetDiff(const int _diff)	{ diff = _diff; }
	void SetNumofHM(const int _numofHM) { numofHM = _numofHM; }
	void SetNumofRK(const int _numofRK) { numofRK = _numofRK; }
	void SetLaunched(const bool _launched) { launched = _launched; }
	void SetHP(const int _hp) { hp = _hp; }

	void Input();
	void Update(int _frame);
	void Render();
	bool Collides(const int _newX, const int _newY);
	
};

