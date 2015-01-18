#include "stdafx.h"
#include "Rocket.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
Rocket::Rocket()
{
	SetText(rocket.c_str());
}


Rocket::~Rocket()
{
}

void Rocket::Update(int _frame)
{

	if (GetAlive())
	{
		int newX = GetX() + GetXVel();
		int newY = GetY() + GetYVel();

		if (_frame % 40 == 0)
		{
			vector<BaseObject*> tempObjects = (*GameState::GetObjects());
			Player* p = dynamic_cast<Player*>(tempObjects[0]);
			for (size_t i = 0; i < tempObjects.size(); i++)
			{
				if (tempObjects[i]->GetID() == ENEMY)
				{
					Enemy* e = dynamic_cast<Enemy*>(tempObjects[i]);
					e->SetHP(0);
					p->SetScore(p->GetScore() + 5);
				}
			}
			
			p->SetLaunched(false);
			SetAlive(false);
		}
		if (_frame % 2 == 0)
		{
			string temp = GetText();
			temp += "  **\n";
			temp += "  **\n";
			SetText(temp.c_str());
		}
		else
		{
			SetText(rocket.c_str());
		}

		SetX(newX);
		SetY(newY);

	}
}