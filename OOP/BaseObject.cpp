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
	for (int i = 0; i < (int)cells.size(); i++)
	{
		cells[i].Show(x, y);
	}
	/*int size = text.length();
	for (int i = 0; i < size; i++)
	{
	if ('\n' == text[i])
	{
	Console::SetCursorPosition(x, Console::CursorTop() + 1);
	}
	else
	cout << text[i];
	}*/
	Console::ResetColor();
}

bool BaseObject::Collides(const int _newX, const int _newY)
{
	int i = 0;
	DList<BaseObject*>& tempObjects = GameState::GetObjects();
	bool collided = false;

	for (; i < (int)tempObjects.Size(); ++i)
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

bool BaseObject::OutOfBounds(const vector<int> _newX, const vector<int> _newY)
{
	bool flag = false;
	for (size_t i = 0; i < GetCells().size(); i++)
	{
		if (_newX[i] >= 0 && _newX[i] <= Console::WindowWidth() && _newY[i] > 0 && _newY[i] < Console::WindowHeight() - 1)
			continue;
		else
			flag = true;
	}
	return flag;
}

void BaseObject::SetCells()
{

	int offsetX, offsetY;
	offsetX = offsetY = 0;
	for (size_t i = 0; i < text.length(); i++)
	{
		if (text[i] == '\n')
		{
			offsetY++;
			offsetX = 0;

		}
		else if (text[i] == ' ')
		{
			offsetX++;
		}
		if (text[i] != '\n' && text[i] != ' ')
		{
			cells.push_back(Cell<int, char>(offsetX++, offsetY, White, Black, text[i]));
		}



	}

}