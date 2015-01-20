#pragma once

/** @brief OBJECT_ID enum to id each object.
*/
enum OBJECT_ID
{
	PLAYER = 0, ENEMY, PLAYER_MISSILE, ENEMY_MISSILE, PLAYER_HOMING_MISSILE, PLAYER_ROCKET
};

/** @brief BaseObject class for the game. Every object in the game is inherited from this class.
*
*	Detailed description follows here.
*	@author Junshu Chen
*	@date Jan 2015
*/
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

	/**
	* Default Constructor.
	*/
	BaseObject();

	/**
	* A Constructor sets up basic members.
	*
	* @param _text an Image2D.
	* @param _fg foreground color.
	* @param _bg background color.
	* @param _x x-position default is 0.
	* @param _y y-position default is 0.
	*/
	BaseObject(const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const short _x = 0, const short _y = 0);

	/**
	* Copy Constructor.
	*/
	BaseObject(BaseObject const& _obj);

	/**
	* Overload Assignment Operator.
	*/
	BaseObject& operator=(BaseObject const& _obj);

	/**
	* virtual Destructor.
	*/
	virtual ~BaseObject();

	/** @name Accessors.
	*/
	///@{ 
	const char* const GetText() const { return text.c_str(); }
	short GetX() const { return x; }
	short GetY() const { return y; }
	unsigned short GetWidth() const { return width; }
	unsigned short GetHeight() const { return height; }
	ConsoleColor GetForeGround() const { return foreground; }
	ConsoleColor GetBackGround() const { return background; }
	bool GetAlive() const { return alive; }
	OBJECT_ID GetID() const { return id; }
	///@}

	/** @name Mutators.
	*/
	///@{ 
	void SetText(const char * const _text){ text = _text; CalWH(); }
	void SetX(const short _x)  { x = _x; }
	void SetY(const short _y)  { y = _y; }
	void SetWidth(const unsigned short _width)  { width = _width; }
	void SetHeight(const unsigned short _height)  { height = _height; }
	void SetForeGround(const ConsoleColor _color)  { foreground = _color; }
	void SetBackGround(const ConsoleColor _color)  { background = _color; }
	void SetAlive(bool _alive) { alive = _alive; }
	void SetID(const OBJECT_ID _id)  { id = _id; }
	///@}

	/**
	* Calculate width and height of Image2D.
	*/
	void CalWH();

	/**
	* Handle User input.
	*/
	virtual void Input();

	/**
	* Update current object.
	*@param _frame Global frame count.
	*/
	virtual void Update(int _frame);

	/**
	* render current object.
	*/
	virtual void Render();

	/**
	* Take in a coordination to see if there is a collision or not. Different child class may have different colliding rule so
	* virtual to allow override.
	* @param _newX x coordinate will be moved to in next frame.
	* @param _newY y coordinate will be moved to in next frame.
	* @return a boolean indicate whether it will collide or not.
	*/
	virtual bool Collides(const int _newX, const int _newY);

	/**
	* Take in a coordination to see if it is out of bounds or not.
	* @param _newX x coordinate will be moved to in next frame.
	* @param _newY y coordinate will be moved to in next frame.
	* @return a boolean indicate if it will be out of bounds.
	*/
	bool OutOfBounds(const int _newX, const int _newY);
};

