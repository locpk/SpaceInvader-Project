#pragma once
#include "BaseObject.h"
class Enemy :
	public BaseObject
{
private:
	int hp = 100;
	int velocity = 1;
public:
	Enemy();
	Enemy(const int _velocity,
		const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const short _x = 0, const short _y = 0);
	~Enemy();

	//accessors 
	int GetVelocity() const { return velocity; }
	int GetHP() const { return hp; }
	//mutators
	void SetVelocity(const int _velocity) { velocity = _velocity; }
	void SetHP(const int _hp) { hp = _hp; }

	void Input();
	void Update(int _frame);
	void Render();
	bool Collides(const int _newX, const int _newY);
};

