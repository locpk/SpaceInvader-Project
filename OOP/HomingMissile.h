#pragma once
#include "Missile.h"


class HomingMissile : public Missile
{


public:
	HomingMissile();
	~HomingMissile();

	void Update(int _frame);

};

