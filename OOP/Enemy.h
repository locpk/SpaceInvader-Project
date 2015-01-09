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
		const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x = 0, short _y = 0);
	Enemy(const Enemy& _obj);
	Enemy& operator=(const Enemy& _obj);
	~Enemy();

	//accessors 
	int GetVelocity() const { return velocity; }

	//mutators
	void SetVelocity(const int _velocity) { velocity = _velocity; }
};
