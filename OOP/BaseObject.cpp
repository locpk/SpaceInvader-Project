#include "stdafx.h"
#include "BaseObject.h"
#include "Game.h"


BaseObject::BaseObject()
{
	text = NULL;
	x = y = -1;
	width = height = -1;
	foreground = White;
	background = Black;
}
BaseObject::BaseObject(const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x, short _y)
{
	text = NULL;
	SetX(_x);
	SetY(_y);
	SetText(_text);
	SetForeGround(_fg);
	SetBackGround(_bg);
}
BaseObject::BaseObject(BaseObject const& _obj)
{
	text = NULL;
	SetX(_obj.x);
	SetY(_obj.y);
	SetText(_obj.text);
	SetForeGround(_obj.foreground);
	SetBackGround(_obj.background);
}
BaseObject& BaseObject::operator=(BaseObject const& _obj)
{
	if (this != &_obj)
	{
		SetX(_obj.x);
		SetY(_obj.y);
		SetText(_obj.text);
		SetForeGround(_obj.foreground);
		SetBackGround(_obj.background);
	}
	return *this;
}
BaseObject::~BaseObject()
{
	delete[] text;
}





void BaseObject::CalWH()
{
	int i = 0;
	height = 1;
	width = 0;
	int size = strlen(text);
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
	int size = strlen(text);
	for (int i = 0; i < size; i++)
	{
		if ('\n' == text[i])
		{
			Console::SetCursorPosition(x, Console::CursorTop() + 1);
		}
		else
			cout << text[i];
	}
}

bool BaseObject::Collides(const BaseObject* const _obj, const int _newX, const int _newY)
{
	int i = 0;
	BaseObject** tempObjects = Game::GetObjects();
	bool collided = false;

	for (; i < 2; ++i)
	{
		if (tempObjects[i] != _obj)
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


	}
	return collided;
}

bool BaseObject::OutOfBounds(const int _newX, const int _newY)
{
	if (_newX >= 0 && _newX <= Console::WindowWidth() - GetWidth() && _newY > 0 && _newY <= Console::WindowHeight() - GetHeight())
		return false;
	else
		return true;
}