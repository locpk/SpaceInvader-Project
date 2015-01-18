#include "stdafx.h"
#include "GameState.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"

vector<BaseObject*> GameState::gameObjects;


GameState::GameState()
{
	gameObjects.push_back(new Player("ss",0,0,"  __\n| \"\"\"\\-=\n(____)",Cyan,Black,Console::WindowWidth() >> 1,Console::WindowHeight()>>1));

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
		Exit();
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
	iter = gameObjects.begin();
	while (iter != gameObjects.end())
	{
		if (!(*iter)->GetAlive())
		{
			delete *iter;
			gameObjects.erase(iter--);
		}

		++iter;
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
	cin >> name;
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
	//Game is over, save out my score
	System::Console::Clear();

	System::Console::SetCursorPosition(10, 10);
	Player* p = dynamic_cast<Player*>(gameObjects[0]);
	cout << "Well done " << p->GetName() << ", you earned " << p->GetScore() << " points on a diff of " << p->GetDiff() << "\n\n\n\n";

	fstream bout;
	bout.open("scores.bin", ios_base::binary | ios_base::app | ios_base::out);

	PlayerInfo info;
	info.score = p->GetScore();
	info.diff = p->GetDiff();
	strcpy_s(info.buffer, 32, p->GetName());

	vector<PlayerInfo> scores;
	scores.push_back(info);

	if (bout.is_open())
	{
		
		bout.write((char*)scores.data(), sizeof(PlayerInfo)* scores.size());

		bout.close();
	}
}