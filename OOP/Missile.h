#pragma once
#include "BaseObject.h"

#define velX vel[0]
#define velY vel[1]

/** @brief Missile class for the game.
*	@author Junshu Chen
*	@date Jan 2015
*/
class Missile : public BaseObject
{
private:
	
	vector<int> vel;
public:
	/**
	* Default Constructor.
	*/
	Missile();

	/**
	* Default Destructor.
	*/
	~Missile();

	/** @name Accessors.
	*/
	///@{ 
	void SetVel(int _x, int _y) { velX = _x; velY = _y; }
	void SetXVel(int _x) { velX = _x; }
	void SetYVel(int _y) { velY = _y; }
	///@}

	/** @name Mutators.
	*/
	///@{ 
	int GetXVel() const { return velX; }
	int GetYVel() const { return velY; }
	void GetVel(int& _x, int& _y) const { _x = velX; _y = velY; }
	///@}

	/**
	* Handle Missile's input which does nothing.
	*/
	void Input();

	/** update missile position based on its velocity
	* virtual let child to override.
	*/
	virtual void Update(int _frame);

	/** Render missile on screen.
	*/
	void Render();

	/** Check collision if it is a player missile collide with enemy and decrement enemy HP Add score to player.
	*	if it is an enemy missile collide with player and decrement player HP.
	*/
	bool Collides(const int _newX, const int _newY);
};

