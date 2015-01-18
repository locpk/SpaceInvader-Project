#pragma once

enum OBJECT_ID
{
	PLAYER = 0, ENEMY, PLAYER_MISSILE, ENEMY_MISSILE, PLAYER_HOMING_MISSILE, PLAYER_ROCKET
};
class BaseObject
{
private:
	string text;
	unsigned short width, height;
	ConsoleColor foreground, background;
	short x, y;
	bool alive;
	OBJECT_ID id;
public:
	BaseObject();
	BaseObject(const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const short _x = 0, const short _y = 0);
	BaseObject(BaseObject const& _obj);
	BaseObject& operator=(BaseObject const& _obj);
	virtual ~BaseObject();

	//accessors 
	const char* const GetText() const { return text.c_str(); }
	short GetX() const { return x; }
	short GetY() const { return y; }
	unsigned short GetWidth() const { return width; }
	unsigned short GetHeight() const { return height; }
	ConsoleColor GetForeGround() const { return foreground; }
	ConsoleColor GetBackGround() const { return background; }
	bool GetAlive() const { return alive; }
	OBJECT_ID GetID() const { return id; }


	//mutators 
	void SetText(const char * const _text){ text = _text; CalWH(); }
	void SetX(const short _x)  { x = _x; }
	void SetY(const short _y)  { y = _y; }
	void SetWidth(const unsigned short _width)  { width = _width; }
	void SetHeight(const unsigned short _height)  { height = _height; }
	void SetForeGround(const ConsoleColor _color)  { foreground = _color; }
	void SetBackGround(const ConsoleColor _color)  { background = _color; }
	void SetAlive(bool _alive) { alive = _alive; }
	void SetID(const OBJECT_ID _id)  { id = _id; }

	void CalWH();

	virtual void Input();
	virtual void Update(int _frame);
	virtual void Render();

	virtual bool Collides(const int _newX, const int _newY);
	bool OutOfBounds(const int _newX, const int _newY);
};

