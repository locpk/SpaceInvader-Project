#include "stdafx.h"
#include "GameState.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"
#include "Game.h"
vector<BaseObject*> GameState::gameObjects;


GameState::GameState()
{
	gameObjects.push_back(new Player("Bob",0,0,"  __\n| \"\"\"\\-=\n(____)",Cyan,Black,Console::WindowWidth() >> 1,Console::WindowHeight()>>1));
}


GameState::~GameState()
{
	int i = 0;
	for (; i < (int)gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}

}

void GameState::Input()
{
	int i = 0;
	for (; i < (int)gameObjects.size(); i++)
	{
		gameObjects[i]->Input();
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Game::ChangeState(MENU_STATE);
	}
}
void GameState::Update(int _frame)
{
	int i = 0;
	for (; i < (int)gameObjects.size(); i++)
	{
		gameObjects[i]->Update(_frame);
	}

	vector<BaseObject*>::iterator iter;
	iter = gameObjects.begin() + 1;
	while (iter != gameObjects.end())
	{
		if (!(*iter)->GetAlive())
		{
			delete *iter;
			gameObjects.erase(iter--);
		}

		++iter;
	}
	// Game over if player is dead
	if (!gameObjects[PLAYER_SUB]->GetAlive())
	{
		Game::ChangeState(MENU_STATE);
	}
}
void GameState::Render()
{
	int i = 0;
	for (; i <(int)gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}
}
	 
void GameState::Enter()
{
	Console::Clear();
	Player* p = dynamic_cast<Player*>(gameObjects[0]);
	Console::FlushKeys();

	string name;
	cout << "What's your name? : _\b";
	getline(cin, name);
	if (name.length() == 0)
	{
		name = "Bob";
	}
	p->SetName(name.c_str());

	if (GetInfo().diff == 0)
		GetInfo().diff = 1;

	if (GetInfo().enemyNum == 0)
		GetInfo().enemyNum = 1;

	p->SetDiff(GetInfo().diff);


	int i = 0;
	for (; i < GetInfo().enemyNum; ++i)
	{
		Enemy* e = new Enemy();
		e->SetX(2 * i + 1);
		e->SetY(2 * i +1);

		gameObjects.push_back(e);
	}
}
void GameState::Exit()
{
	//Game over
	System::Console::Clear();

	System::Console::SetCursorPosition(10, 10);
	Player* p = dynamic_cast<Player*>(gameObjects[0]);
	PlayerInfo info;
	info.score = p->GetScore();
	info.diff = p->GetDiff();
	strcpy_s(info.buffer, 32, p->GetName());

	string tempLine = p->GetName();
	tempLine += " earned ";
	tempLine += to_string(p->GetScore());
	tempLine += " points on a difficulty of ";
	tempLine += to_string(p->GetDiff());
	for (size_t i = 0; i < tempLine.length(); i++)
	{
		Sleep(50);
		cout << tempLine[i];
	}
	


	

	vector<PlayerInfo> scores;
	scores.push_back(info);
	fstream bout,tout;
	bout.open("scores.bin", ios_base::binary | ios_base::app | ios_base::out);
	tout.open("scores.txt", ios_base::app | ios_base::out);

	if (bout.is_open())
	{
		
		bout.write((char*)scores.data(), sizeof(PlayerInfo)* scores.size());

		bout.close();
	}
	if (tout.is_open())
	{
		tout << p->GetName() << "\t" << p->GetScore() << "\t" << p->GetDiff() << "\n";
		tout.close();
	}
	Sleep(1500);
	

	//Replay
	//Console::FlushKeys();
	//Console::SetCursorPosition((Console::WindowWidth() >> 1) - 10, Console::WindowHeight() >> 1);
	//cout << "Wanna try again? Enter 1 to replay. otherwise to Main menu.";
	//Sleep(150);
	//int choice = 0;
	//if (cin >> choice && choice == 1)
	//{
	//	gameObjects[PLAYER_SUB]->SetAlive(true);
	//	Player* p = dynamic_cast<Player*>(gameObjects[PLAYER_SUB]);
	//	p->SetHP(100);
	//	p->SetForeGround(Cyan);

	//	for (int i = 1; i < (int)gameObjects.size(); i++)
	//	{
	//		if (ENEMY == gameObjects[i]->GetID())
	//		{
	//			Enemy* e = dynamic_cast<Enemy*>(gameObjects[i]);
	//			e->SetAlive(true);
	//			e->SetHP(100);
	//			e->SetForeGround(White);
	//		}
	//	}
	//}
	//else
	//	Game::ChangeState(MENU_STATE);
	//

}