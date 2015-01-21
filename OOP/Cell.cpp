#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
}


Cell::Cell(int _x, int _y, ConsoleColor _fg, ConsoleColor _bg, char _sym)
{
	oX = _x;
	oY = _y;
	fg = _fg;
	bg = _bg;
	sym = _sym;
}

bool Cell::Show(int _left, int _top) const
{
	if (oX + _left < 0 && oX + _left > Console::WindowWidth() && oY + _top < 0 && oY + _top > Console::WindowHeight())
	{
		return false;
	}
	else
	{
		Console::SetCursorPosition(oX + _left, oY + _top);
		cout << sym;
		return true;
	}
}