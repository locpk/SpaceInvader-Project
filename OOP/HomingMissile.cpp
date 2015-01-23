#include "stdafx.h"
#include "HomingMissile.h"
#include "GameState.h"

HomingMissile::HomingMissile()
{
	
}


HomingMissile::~HomingMissile()
{
}




void HomingMissile::Update(int _frame)
{
	DList<BaseObject*>& tempObjects = GameState::GetObjects();
	vector<int> enemies;
	for (int i = 0; i < tempObjects.Size(); i++)
	{
		if (tempObjects[i]->GetID() == ENEMY)
			enemies.push_back(i);
	}
	int target = enemies[rand() % enemies.size()];
	bool left, right, up, down;
	left = right = up = down = false;

	if (GetAlive())
	{

		if ((tempObjects)[target]->GetX() > GetX())
			right = true;
		if ((tempObjects)[target]->GetX() < GetX())
			left = true;
		if ((tempObjects)[target]->GetY() < GetY())
			up = true;
		if ((tempObjects)[target]->GetY() > GetY())
			down = true;

		if ((tempObjects)[target]->GetX() > GetX() && (tempObjects)[target]->GetY() == GetY())
		{
			right = true;
			down = false;
			up = false;
			left = false;
		}
		if ((tempObjects)[target]->GetX() < GetX() && (tempObjects)[target]->GetY() == GetY())
		{
			left = true;
			down = false;
			up = false;
			right = false;
		}

		if (up && left == false && right == false)
		{
			SetText("|");
			SetXVel(0);
			SetYVel(-1);
		}
		if (down && left == false && right == false)
		{
			SetText("|");
			SetXVel(0);
			SetYVel(1);
		}
		else if (right && up == false && down == false)
		{
			SetText("--");
			SetXVel(1);
			SetYVel(0);

		}
		else if (left && up == false && down == false)
		{
			SetText("--");
			SetXVel(-1);
			SetYVel(0);
		}
		else if (up && left && right == false && down == false)
		{
			SetText("\\");
			SetXVel(-1);
			SetYVel(-1);
		}
		else if (up && right && left == false && down == false)
		{
			SetText("/");
			SetXVel(1);
			SetYVel(-1);
		}
		else if (down && right && up == false && left == false)
		{
			SetText("\\");
			SetXVel(1);
			SetYVel(1);
		}
		else if (down && left && up == false && right == false)
		{
			SetText("/");
			SetXVel(-1);
			SetYVel(1);
		}



		int newX = GetX() + GetXVel();
		int newY = GetY() + GetYVel();

		if (Collides(newX, newY) || OutOfBounds(newX, newY))
		{
			SetAlive(false);
		}
		else
		{
			SetX(newX);
			SetY(newY);
		}

	}
}


