#pragma once

template<class Offset = int , class Symbol = char>
struct Cell
{
	Offset oX, oY;
	ConsoleColor fg, bg;
	Symbol sym;

	Cell() { }
	Cell(Offset _x, Offset _y, ConsoleColor _fg, ConsoleColor _bg, Symbol _sym);

	bool Show(int _left, int _top) const;

	Offset& operator[](int _index);
	Offset const& operator[](int _index) const;
};


template<typename Offset, typename Symbol>
Cell<Offset, Symbol>::Cell(Offset _x, Offset _y, ConsoleColor _fg, ConsoleColor _bg, Symbol _sym) : oX(_x), oY(_y), fg(_fg), bg(_bg), sym(_sym)
{
}


template<typename Offset, typename Symbol>
bool Cell<Offset, Symbol>::Show(int _left, int _top) const
{
	if (oX + _left < 1 && oX + _left > Console::WindowWidth() && oY + _top < 1 && oY + _top > Console::WindowHeight() - 1)
	{
		return false;
	}
	else
	{
		Console::SetCursorPosition(oX + _left, oY + _top);
		Console::ForegroundColor(fg);
		Console::BackgroundColor(bg);
		cout << sym;
		Console::ResetColor();
		return true;
	}
}

template<typename Offset, typename Symbol>
Offset& Cell<Offset, Symbol>::operator[](int _index)
{
	return _index == 0 ? oX : oY;
}

template<typename Offset, typename Symbol>
Offset const& Cell<Offset, Symbol>::operator[](int _index) const
{
	return _index == 0 ? oX : oY;
}