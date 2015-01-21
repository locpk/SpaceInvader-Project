#pragma once


struct Cell
{
	int oX, oY;
	ConsoleColor fg, bg;
	char sym;

	Cell() { }
	Cell(int _x, int _y, ConsoleColor _fg, ConsoleColor _bg, char _sym);

	bool Show(int _left, int _top) const;
};

