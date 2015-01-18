#include "stdafx.h"
#include "BaseObject.h"
#include "Game.h"
#include "GameState.h"
#include "Enemy.h"

BaseObject::BaseObject()
{
	x = y = -1;
	width = height = -1;
	foreground = White;
	background = Black;
}
BaseObject::BaseObject(const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x, short _y)
{
	SetX(_x);
	SetY(_y);
	SetText(_text);
	SetForeGround(_fg);
	SetBackGround(_bg);
}
BaseObject::BaseObject(BaseObject const& _obj)
{
	SetX(_obj.x);
	SetY(_obj.y);
	SetText(_obj.text.c_str());
	SetForeGround(_obj.foreground);
	SetBackGround(_obj.background);
}
BaseObject& BaseObject::operator=(BaseObject const& _obj)
{
	if (this != &_obj)
	{
		SetX(_obj.x);
		SetY(_obj.y);
		SetText(_obj.text.c_str());
		SetForeGround(_obj.foreground);
		SetBackGround(_obj.background);
	}
	return *this;
}
BaseObject::~BaseObject()
{
}





void BaseObject::CalWH()
{
	int i = 0;
	height = 1;
	width = 0;
	int size = text.length();
	for (; i < size; ++i)
	{
		if (text[i] == '\n')
			++height;
		else
			++width;
	}

	width /= height;

}
void BaseObject::Input()
{

}
void BaseObject::Update(int _frame)
{

}
void BaseObject::Render()
{
	Console::SetCursorPosition(x, y);
	Console::ForegroundColor(foreground);
	Console::BackgroundColor(background);
	int size = text.length();
	for (int i = 0; i < size; i++)
	{
		if ('\n' == text[i])
		{
			Console::SetCursorPosition(x, Console::CursorTop() + 1);
		}
		else
			cout << text[i];
	}
	Console::ResetColor();
}

bool BaseObject::Collides(const int _newX, const int _newY)
{
	int i = 0;
	vector<BaseObject*> tempObjects = (*GameState::GetObjects());
	bool collided = false;

	for (; i < (int)tempObjects.size(); ++i)
	{

		int left = tempObjects[i]->GetX();
		int top = tempObjects[i]->GetY();
		int right = left + tempObjects[i]->GetWidth();
		int bottom = top + tempObjects[i]->GetHeight();

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

	}
	return collided;
}

bool BaseObject::OutOfBounds(const int _newX, const int _newY)
{
	if (_newX >= 0 && _newX <= Console::WindowWidth() - GetWidth() && _newY > 0 && _newY <= Console::WindowHeight() - 1 - GetHeight())
		return false;
	else
		return true;
}