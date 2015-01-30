#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include"GameState.h"
#include "Missile.h"
#include "Game.h"

Enemy::Enemy()
{
	SetID(ENEMY);
	SetText("<-O->");
	SetX(System::Console::WindowWidth() >> 1);
	SetY(4);
}
Enemy::Enemy(const int _velocity,
	const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg,  const int _hp, short _x, short _y) : BaseObject(_text, _fg, _bg, _x, _y)
{
	SetID(ENEMY);
	SetHP(_hp);
}

Enemy::~Enemy()
{

}


void Enemy::Input()
{

}

void Enemy::Update(int _frame)
{
	if (_frame % 1 == 0 && (Game::GetCheats() & ENEMY_MOVE_FLAG))
	{


		vector<int> newX;
		vector<int> newY;
		for (size_t i = 0; i < GetCells().size(); i++)
		{
			newX.push_back(GetX() + velocity + GetCells()[i][0]);
			newY.push_back(GetY()+ GetCells()[i][1]);
		}

		if (Collides(newX, newY) || OutOfBounds(newX, newY))
		{
			velocity = -velocity;
		}
		else
		{
			SetX(GetX() + velocity);
		}

		//enemy hp indication 
		if (GetHP() <= 20)
			SetForeGround(Red);
		if (GetHP() <= 0)
		{
			SetAlive(false);
			DList<BaseObject*>& tempObjects = GameState::GetObjects();
			Player* p = dynamic_cast<Player*>(tempObjects[0]);
			p->SetKillCount(p->GetKillCount() + 1);
		}

	}

	//enemy shooting every 10 frames
	if (_frame % 10 == 0 && (Game::GetCheats() & ENEMY_SHOOT_FLAG))
	{
		DList<BaseObject*>& tempObjects = GameState::GetObjects();
		Missile* m = new Missile();
		m->SetID(ENEMY_MISSILE);
		m->SetVel(0, 1);
		m->SetAlive(true);
		m->SetX(GetX() + (GetWidth() >> 1));
		m->SetY(GetY());
		(tempObjects).push_back(m);
	}
}

void Enemy::Render()
{
	if (GetAlive())
		BaseObject::Render();
}

bool Enemy::Collides(const vector<int> _newX, const vector<int> _newY)
{
	if (Game::GetCheats() & GHOST_FLAG)
	{
		return false;
	}
	int i = 0;
	DList<BaseObject*>& tempObjects = GameState::GetObjects();
	bool collided = false;
	int left, top, right, bottom;
	left = top = right = bottom = 0;

	for (; i < (int)tempObjects.Size(); ++i)
	{
		switch (tempObjects[i]->GetID())
		{

		case PLAYER:
			for (size_t j = 0; j < tempObjects[i]->GetCells().size(); j++)
			{
				for (size_t c = 0; c < _newX.size(); c++)
				{
					if (_newX[c] == (tempObjects[i]->GetCells()[j][0] + tempObjects[i]->GetX()) && _newY[c] == (tempObjects[i]->GetCells()[j][1] + tempObjects[i]->GetY()))
					{
						return true;
					}
				}
			}
			break;
		default:
			break;
		}

	}
	return collided;
}