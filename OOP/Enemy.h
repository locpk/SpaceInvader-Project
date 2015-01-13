#pragma once
#include "BaseObject.h"
class Enemy :
	public BaseObject
{
private:
	int velocity = 1;
public:
	Enemy();
	Enemy(const int _velocity,
		const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const short _x = 0, const short _y = 0);
	~Enemy();

	//accessors 
	int GetVelocity() const { return velocity; }

	//mutators
	void SetVelocity(const int _velocity) { velocity = _velocity; }


	void Input();
	void Update(int _frame);
	void Render();
};

