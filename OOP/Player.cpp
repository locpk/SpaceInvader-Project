#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	name = NULL;
}
Player::Player(const char* const _name, int _score, int _diff,
	const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x, short _y)
	: BaseObject(_text, _fg, _bg, _x, _y)
{
	name = NULL;
	SetName(_name);
	SetScore(_score);
	SetDiff(_diff);
}

Player::Player(const Player& _obj) : BaseObject(_obj)
{
	name = NULL;
	SetName(_obj.name);
	SetScore(_obj.score);
	SetDiff(_obj.diff);
}

Player& Player::operator=(const Player& _obj)
{
	if (this != &_obj)
	{
		BaseObject::operator=(_obj);
		SetName(_obj.name);
		SetScore(_obj.score);
		SetDiff(_obj.diff);
	}
	return *this;
}

Player::~Player()
{
	delete[] name;
}

void Player::Input()
{
	int dx, dy;
	dx = dy = 0;

	if (GetAsyncKeyState('W')) dy = -1;
	if (GetAsyncKeyState('S')) dy = 1;
	if (GetAsyncKeyState('A')) dx = -1;
	if (GetAsyncKeyState('D')) dx = 1;

	if (dx || dy)
	{
		int newX = GetX() + dx;
		int newY = GetY() + dy;

		if (newX >= 0 && newX <= Console::WindowWidth() - GetWidth())
			SetX(newX);
		if (newY > 0 && newY <= Console::WindowHeight() - GetHeight())
			SetY(newY);
	}
}
void Player::Update()
{

}
void Player::Render()
{
	Console::SetCursorPosition(0, 0);
	cout << "Name: " << name;
	Console::SetCursorPosition(Console::WindowWidth() >> 1, 0);
	cout << "Score: " << score;
	Console::SetCursorPosition(Console::WindowWidth() - 15, 0);
	cout << "Difficulty: " << diff;
	BaseObject::Render();
}
