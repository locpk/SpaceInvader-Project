#include "stdafx.h"
#include "Player.h"
#include "GameState.h"
#include "Missile.h"
#include "HomingMissile.h"
#include "Rocket.h"
#include "Game.h"
Player::Player()
{
	SetID(PLAYER);
}
Player::Player(const char* const _name, int _score, int _diff,
	const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x, short _y)
	: BaseObject(_text, _fg, _bg, _x, _y)
{
	SetID(PLAYER);
	SetName(_name);
	SetScore(_score);
	SetDiff(_diff);
}

Player::Player(const Player& _obj) : BaseObject(_obj)
{
	SetID(PLAYER);
	SetName(_obj.name.c_str());
	SetScore(_obj.score);
	SetDiff(_obj.diff);
}

Player& Player::operator=(const Player& _obj)
{
	if (this != &_obj)
	{
		BaseObject::operator=(_obj);
		SetName(_obj.name.c_str());
		SetScore(_obj.score);
		SetDiff(_obj.diff);
	}
	return *this;
}

Player::~Player()
{

}

void Player::Input()
{
	int dx, dy;
	dx = dy = 0;
	DList<BaseObject*>& tempObjects = GameState::GetObjects();

	if (GetAsyncKeyState('W')) dy = -1;
	if (GetAsyncKeyState('S')) dy = 1;
	if (GetAsyncKeyState('A')) dx = -1;
	if (GetAsyncKeyState('D')) dx = 1;

	if (dx || dy)
	{
		/*int newX = GetX() + dx;
		int newY = GetY() + dy;*/
		vector<int> newX;
		vector<int> newY;
		for (size_t i = 0; i < GetCells().size(); i++)
		{
			newX.push_back(GetX() + dx + GetCells()[i][0]);
			newY.push_back(GetY() + dy + GetCells()[i][1]);
		}
		
		if (!OutOfBounds(newX, newY) && !Collides(newX, newY))
		{

			SetX(GetX() + dx); SetY(GetY() + dy);
		}

	}


	if (GetAsyncKeyState(VK_NUMPAD4) && !buttonPressed)
	{
		buttonPressed = true;
		Missile* m = new Missile();
		m->SetID(PLAYER_MISSILE);
		m->SetVel(0, -1);
		m->SetAlive(true);
		m->SetX(GetX() + (GetWidth() >> 1));
		m->SetY(GetY());
		tempObjects.push_back(m);
	}
	if (GetAsyncKeyState(VK_NUMPAD5) && !buttonPressed && GetNumofHM() > 0)
	{
		buttonPressed = true;
		HomingMissile* h = new HomingMissile();
		h->SetID(PLAYER_HOMING_MISSILE);
		h->SetVel(0, -1);
		h->SetAlive(true);
		h->SetX(GetX() + (GetWidth() >> 1));
		h->SetY(GetY());
		(tempObjects).push_back(h);
		SetNumofHM(GetNumofHM() - 1);
	}
	if (GetAsyncKeyState(VK_NUMPAD6) && !buttonPressed && GetNumofRK() > 0 && !GetLaunched())
	{
		buttonPressed = true;
		SetLaunched(true);
		Rocket* r = new Rocket();
		r->SetID(PLAYER_ROCKET);
		r->SetVel(0, -1);
		r->SetAlive(true);
		r->SetX(GetX() + (GetWidth() >> 1));
		r->SetY(GetY() - 10);
		(tempObjects).push_back(r);
		SetNumofRK(GetNumofRK() - 1);
	}

	if (GetAsyncKeyState(VK_F1) && !buttonPressed)
	{
		buttonPressed = true;
		Game::GetCheats() ^= ALIVE_FLAG;
	}

	if (GetAsyncKeyState(VK_F2) && !buttonPressed)
	{
		buttonPressed = true;
		Game::GetCheats() ^= GHOST_FLAG;
	}

	if (GetAsyncKeyState(VK_F3) && !buttonPressed)
	{
		buttonPressed = true;
		Game::GetCheats() ^= ENEMY_MOVE_FLAG;
	}

	if (GetAsyncKeyState(VK_F4) && !buttonPressed)
	{
		buttonPressed = true;
		Game::GetCheats() ^= ENEMY_SHOOT_FLAG;
	}

}
void Player::Update(int _frame)
{
	if (!GetAsyncKeyState(VK_NUMPAD4) && !GetAsyncKeyState(VK_NUMPAD5) && !GetAsyncKeyState(VK_NUMPAD6) && !GetAsyncKeyState(VK_F1) && 
		!GetAsyncKeyState(VK_F2) && !GetAsyncKeyState(VK_F3) && !GetAsyncKeyState(VK_F4))
	{
		buttonPressed = false;
	}

	if (GetHP() <= 20)
	{
		SetForeGround(DarkRed);
	}
	if (GetHP() <= 0)
	{
		SetAlive(false);
	}
}
void Player::Render()
{
	Console::SetCursorPosition(0, 0);
	bitset<8> x(Game::GetCheats());
	cout << "Name: " << name << " HP: " << hp << " Kills: " << killCount << " Cheats: " << x;
	Console::SetCursorPosition(Console::WindowWidth() >> 1, 0);
	cout << "Score: " << score;
	Console::SetCursorPosition(Console::WindowWidth() - 15, 0);
	cout << "Difficulty: " << diff;
	Console::SetCursorPosition(0, Console::WindowHeight());
	cout << "Number of Homing Missiles: ";
	for (int i = 0; i < numofHM; i++)
	{
		cout << " | ";
	}
	Console::SetCursorPosition(Console::WindowWidth() >> 1, Console::WindowHeight());
	cout << "Number of Rockets: ";
	for (int i = 0; i < numofRK; i++)
	{
		cout << " ^ ";
	}
	if (GetAlive())
		BaseObject::Render();
}

bool Player::Collides(const vector<int> _newX, const vector<int> _newY)
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

		case ENEMY:
			/*left = tempObjects[i]->GetX();
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

				collided = true;
				break;
			}*/
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

void Player::Reset()
{
	SetAlive(true);
	SetHP(100);
	SetForeGround(Cyan);
	SetKillCount(0);
	SetLaunched(false);
	SetNumofHM(10);
	SetNumofRK(5);
	SetScore(0);
}