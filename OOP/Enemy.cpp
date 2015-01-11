#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	SetText("<-O->");
	SetX(System::Console::WindowWidth() >> 1);
	SetY(3);
}
Enemy::Enemy(const int _velocity,
	const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x, short _y) : BaseObject(_text, _fg, _bg, _x, _y)
{

}

Enemy::~Enemy()
{

}


void Enemy::Input()
{

}

void Enemy::Update(int _frame)
{
	if (_frame % 10 == 0)
	{
		int newX = GetX() + velocity;
		int newY = GetY() + 1;

		if (Collides(this,newX, newY) || OutOfBounds(newX,newY))
		{
			velocity = -velocity;
		}
		else
		{
			SetX(GetX() + velocity);
		}
		
		
		
	}
}

void Enemy::Render()
{
	BaseObject::Render();
}