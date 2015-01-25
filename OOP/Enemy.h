#pragma once
#include "BaseObject.h"

/**
*	Enemy class to define enemy properties and behaviors.
*	@author Junshu Chen
*	@date Jan 2015
*/
class Enemy : public BaseObject
{
private:
	int hp = 100;
	int velocity = 1;
public:

	/**
	* Default Constructor.
	*/
	Enemy();

	/**
	* A Constructor sets up every undefined members.
	*
	* @param _velocity.
	* @param _score.
	* @param _text an Image2D.
	* @param _fg foreground color.
	* @param _bg background color.
	* @param _x x-position default is 0.
	* @param _y y-position default is 0.
	*/
	Enemy(const int _velocity,
		const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, const int _hp, const short _x = 0, const short _y = 0);

	/**
	* Destructor.
	*/
	~Enemy();

	/** @name Accessors.
	*/
	///@{ 
	int GetVelocity() const { return velocity; }
	int GetHP() const { return hp; }
	///@}

	/** @name Mutators.
	*/
	///@{ 
	void SetVelocity(const int _velocity) { velocity = _velocity; }
	void SetHP(const int _hp) { hp = _hp; }
	///@}

	/**
	* Handle enemy's input, so far it does nothing.
	*/
	void Input();

	/**
	* Update enemy movement and firing.
	*@param _frame global frame count.
	*/
	void Update(int _frame);

	/**
	* Render enemy on screen.
	*/
	void Render();

	/**
	* Check collisions with player.
	*/
	bool Collides(const int _newX, const int _newY);
};

