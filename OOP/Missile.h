#pragma once
#include "BaseObject.h"

#define velX vel[0]
#define velY vel[1]
class Missile : public BaseObject
{
private:
	
	vector<int> vel;
public:
	Missile();
	~Missile();

	void SetVel(int _x, int _y) { velX = _x; velY = _y; }
	void SetXVel(int _x) { velX = _x; }
	void SetYVel(int _y) { velY = _y; }

	int GetXVel() const { return velX; }
	int GetYVel() const { return velY; }
	void GetVel(int& _x, int& _y) const { _x = velX; _y = velY; }

	void Input();
	virtual void Update(int _frame);
	void Render();
	bool Collides(const int _newX, const int _newY);
};

