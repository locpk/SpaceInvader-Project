#pragma once
#include "Missile.h"

/** @brief Rocket class inherited from Missile class.
*	@author Junshu Chen
*	@date Jan 2015
*/
class Rocket : public Missile
{
private:
	string rocket = "  /\\\n  ||  \n  ||  \n /||\\\n/:||:\\\n|:||:|\n|/||\\|\n  **\n  **\n";
public:
	Rocket();
	~Rocket();
	void Update(int _frame);
};

