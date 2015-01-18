#pragma once
#include "Missile.h"
class Rocket :
	public Missile
{
private:
	string rocket = "  /\\\n  ||  \n  ||  \n /||\\\n/:||:\\\n|:||:|\n|/||\\|\n  **\n  **\n";
public:
	Rocket();
	~Rocket();
	void Update(int _frame);
};

