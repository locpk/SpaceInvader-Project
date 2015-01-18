#include "stdafx.h"
#include "Enemy.h"
#include"GameState.h"

Enemy::Enemy()
{
	SetID(ENEMY);
	SetText("<-O->");
	SetX(System::Console::WindowWidth() >> 1);
	SetY(3);
}
Enemy::Enemy(const int _velocity,
	const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x, short _y) : BaseObject(_text, _fg, _bg, _x, _y)
{
	SetID(ENEMY);
	SetText("<-O->");
	SetX(System::Console::WindowWidth() >> 1);
	SetY(3);
}

Enemy::~Enemy()
{

}


void Enemy::Input()
{

}

void Enemy::Update(int _frame)
{
	if (_frame % 1 == 0)
	{
		int newX = GetX() + velocity;
		int newY = GetY();

		if (Collides(newX, newY) || OutOfBounds(newX, newY))
		{
			velocity = -velocity;
		}
		else
		{
			SetX(GetX() + velocity);
		}
		if (GetHP() <= 20)
			SetForeGround(Red);
		if (GetHP() <= 0)
			SetAlive(false);
	}
}

void Enemy::Render()
{
	if (GetAlive())
		BaseObject::Render();
}

bool Enemy::Collides(const int _newX, const int _newY)
{
	int i = 0;
	vector<BaseObject*> tempObjects = (*GameState::GetObjects());
	bool collided = false;
	int left, top, right, bottom;
	left = top = right = bottom = 0;

	for (; i < (int)tempObjects.size(); ++i)
	{
		switch (tempObjects[i]->GetID())
		{

		case PLAYER:
			 left = tempObjects[i]->GetX();
			 top = tempObjects[i]->GetY();
			 right = left + tempObjects[i]->GetWidth();
			 bottom = top + tempObjects[i]->GetHeight();

			if (_newX >= right ||
				_newX + GetWidth() <= left ||
				_newY >= bottom ||
				_newY + GetHeight() <= top)
			{
				collided = false;
			}
			else
			{
				collided = true;
				break;
			}
			break;
		default:
			break;
		}

	}
	return collided;
}