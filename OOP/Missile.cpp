#include "stdafx.h"
#include "Missile.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
#include "Rocket.h"
Missile::Missile()
{
	SetText("*");
	vel.resize(2);
	velX = 0;
	velY = 0;
}


Missile::~Missile()
{
}

void Missile::Input()
{

}

void Missile::Update(int _frame)
{


	if (GetAlive())
	{
		int newX = GetX() + velX;
		int newY = GetY() + velY;

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
void Missile::Render()
{
	if (GetAlive())
	{
		BaseObject::Render();
	}

}

bool Missile::Collides(const int _newX, const int _newY)
{
	vector<BaseObject*> tempObjects = (*GameState::GetObjects());
	bool collided = false;
	int left, top, right, bottom;
	left = top = right = bottom = 0;

	switch (GetID())
	{
	case PLAYER_MISSILE:
	case PLAYER_HOMING_MISSILE: // check collision based on the owner. Enemy missiles only collide with player. Player Missile only collide with enemy.
		for (int i = 1; i < (int)tempObjects.size(); i++)
		{
			if (ENEMY == tempObjects[i]->GetID())
			{
				left = tempObjects[i]->GetX();
				top = tempObjects[i]->GetY();
				right = left + tempObjects[i]->GetWidth();
				bottom = top + tempObjects[i]->GetHeight();

				if (_newX >= right ||
					_newX + GetWidth() <= left ||
					_newY >= bottom ||
					_newY + GetHeight() <= top)
				{
					collided = false;
				}
				else
				{
					Player* p = dynamic_cast<Player*>(tempObjects[0]);
					p->SetScore(p->GetScore() + 5);
					Enemy* e = dynamic_cast<Enemy*>(tempObjects[i]);
					e->SetHP(e->GetHP() - 5);
					SetAlive(false); // Set current missile to dead
					collided = true;
					break; // break the inner loop
				}
			}
		}
		break;
	case ENEMY_MISSILE:
		left = tempObjects[PLAYER_SUB]->GetX();
		top = tempObjects[PLAYER_SUB]->GetY();
		right = left + tempObjects[PLAYER_SUB]->GetWidth();
		bottom = top + tempObjects[PLAYER_SUB]->GetHeight();

		if (_newX >= right ||
			_newX + GetWidth() <= left ||
			_newY >= bottom ||
			_newY + GetHeight() <= top)
		{
			collided = false;
		}
		else
		{
			Player* p = dynamic_cast<Player*>(tempObjects[PLAYER_SUB]);
			p->SetHP(p->GetHP() - 5);
			SetAlive(false);
			collided = true;
		}
		break;
	default:
		break;
	}
	return collided;
}

