#pragma once
#include "Missile.h"

/** @brief HomingMissile class derived from Missile Class.
*	@author Junshu Chen
*	@date Jan 2015
*/
class HomingMissile : public Missile
{
private:
	int target;
public:
	HomingMissile();
	~HomingMissile();

	/** 
	* Updating velocity based on enemy position to achieve homing.
	*@param _frame global frame count.
	*/
	void Update(int _frame);

};

