#pragma once
class BaseObject
{
private:
	char* text;
	unsigned short width, height;
	ConsoleColor foreground, background;
	short x, y;
public:
	BaseObject();
	BaseObject(const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x = 0, short _y = 0);
	BaseObject(BaseObject const& _obj);
	BaseObject& operator=(BaseObject const& _obj);
	virtual ~BaseObject();

	//accessors 
	const char* const GetText() const { return text; }
	short GetX() const { return x; }
	short GetY() const { return y; }
	unsigned short GetWidth() const { return width; }
	unsigned short GetHeight() const { return height; }
	ConsoleColor GetForeGround() const { return foreground; }
	ConsoleColor GetBackGround() const { return background; }
	//mutators 
	void SetText(const char * const _text){delete[] text; text = _strdup(_text); CalWH(); }
	void SetX(const short _x)  { x = _x; }
	void SetY(const short _y)  { y = _y; }
	void SetWidth(const unsigned short _width)  { width = _width; }
	void SetHeight(const unsigned short _height)  { height = _height; }
	void SetForeGround(ConsoleColor _color)  { foreground = _color; }
	void SetBackGround(ConsoleColor _color)  { background = _color; }
	
	void CalWH();
	
	virtual void Input();
	virtual void Update(int _frame);
	virtual void Render();

	bool BaseObject::Collides(const BaseObject* const _obj, const int _newX, const int _newY);
	bool BaseObject::OutOfBounds(const int _newX, const int _newY);
};

