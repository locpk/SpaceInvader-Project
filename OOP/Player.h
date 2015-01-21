#pragma once
#include "BaseObject.h"


/** @brief Player info struct for passing info between states and saving scores to file.
*/
struct PlayerInfo
{
	char buffer[32];
	int score;
	int diff;
	int killCount;
};


	/** @brief Player class for the game.
	*
	*	Detailed description follows here.
	*	@author Junshu Chen
	*	@date Jan 2015
	*/
class Player : public BaseObject
{
private:
	string name;
	int score, diff; 
	int hp = 100;
	int numofHM = 10;   // Number of Homing Missiles.
	int numofRK = 5;    //Number of Rockets. 
	int killCount = 0;
	bool buttonPressed = false;   // A boolean for buffered input.
	bool launched = false;   // Set to true if a rocket is launched and not destroyed. 


public:
	/**
	* Default Constructor.
	*/
	Player();

	/**
	* A Constructor sets up every undefined members.
	* 
	* @param _name a C-string of name.
	* @param _score score.
	* @param _diff difficulty.
	* @param _text an Image2D.
	* @param _fg foreground color.
	* @param _bg background color.
	* @param _x x-position default is 0.
	* @param _y y-position default is 0.
	*/
	Player(const char* const _name, int _score, int _diff, 
		const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const short _x = 0, const short _y = 0);

	/**
	* Copy Constructor.
	*/
	Player(const Player& _obj);

	/**
	* Overload Assignment Operator.
	*/
	Player& operator=(const Player& _obj);

	/**
	* Destructor.
	*/
	~Player();


	/** @name Accessors.
	*/
	///@{ 
	const char* const GetName() const { return name.c_str(); }
	int GetScore() const { return score; }
	int GetDiff() const { return diff; }
	int GetNumofHM()const { return numofHM; }
	int GetNumofRK()const { return numofRK; }
	bool GetLaunched() const{ return launched; }
	int GetHP() const { return hp; }
	int GetKillCount()const{ return killCount; }
	///@}

	/** @name Mutators.
	*/
	///@{ 
	void SetName(const char* const _name) { name = _name; }
	void SetScore(const int _score) { score = _score; }
	void SetDiff(const int _diff)	{ diff = _diff; }
	void SetNumofHM(const int _numofHM) { numofHM = _numofHM; }
	void SetNumofRK(const int _numofRK) { numofRK = _numofRK; }
	void SetLaunched(const bool _launched) { launched = _launched; }
	void SetHP(const int _hp) { hp = _hp; }
	void SetKillCount(const int _killCount){ killCount = _killCount; }
	///@}


	/**
	* Handle player's input such as shooting missiles and movement.
	*/
	void Input();

	/**
	* Update player status based on frames.
	* @param _frame global frame count.
	*/
	void Update(int _frame);
	
	/**
	* Render HUD and player's ship.
	*/
	void Render();

	/**
	* Check Player collision with enemies.
	* @param _newX x coordinate will be moved to in next frame.
	* @param _newY y coordinate will be moved to in next frame.
	* @return a boolean indicate whether it will collide or not.
	*/
	bool Collides(const int _newX, const int _newY);
	
	void Reset();
};

