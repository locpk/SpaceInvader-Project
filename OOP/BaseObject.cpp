#include "stdafx.h"
#include "BaseObject.h"



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
	width = 0;
	int widthcount = 0;
	height = 1;
	int size = strlen(text);
	for (int i = 0; i < size; i++)
	{
		if ('\n' == text[i])
		{
			if (widthcount > width)
			{
				width = widthcount;
				widthcount = 0;
			}
			height++;
		}
		else
		{
			widthcount++;
		}
			
	}
	
}
void BaseObject::Input()
{

}
void BaseObject::Update()
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