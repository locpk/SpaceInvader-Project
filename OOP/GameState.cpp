#include "stdafx.h"
#include "GameState.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"
#include "Game.h"
#include "Cell.h"
DList<BaseObject*> GameState::gameObjects;


GameState::GameState()
{
	ReadObFromFile();
	gameObjects.push_back(new Player("Bob", 0, 0, readInObjects[1]->GetText(), readInObjects[1]->GetForeGround(), readInObjects[1]->GetBackGround(), readInObjects[1]->GetX(), readInObjects[1]->GetY()));
	

	numofStars = (2 * (rand() % 6 + 5));
	stars = new Cell<>[numofStars];
	GenerateStars();
}


GameState::~GameState()
{
	int i = 0;
	for (; i < gameObjects.Size(); i++)
	{
		delete gameObjects[i];
	}
	for (i = 0; i < (int)readInObjects.size(); i++)
	{
		delete readInObjects[i];
	}
	delete[] stars;

}

void GameState::Input()
{
	int i = 0;
	for (; i < (int)gameObjects.Size(); i++)
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
	for (; i < (int)gameObjects.Size(); i++)
	{
		gameObjects[i]->Update(_frame);
	}

	for (int i = 0; i < gameObjects.Size(); i++)
	{
		if (gameObjects[i]->GetID() == ENEMY && gameObjects[i]->GetAlive() == false)
		{
			delete gameObjects[i];
			gameObjects.erase(i);
			enemyCount--;
		}

	}

	//Respawn enemies if they all dead 
	if (enemyCount <= 0 && waves < MAXWAVES)
	{
		int i = 0;
		for (; i < GetInfo().enemyNum; ++i)
		{
			Enemy* e = new Enemy();
			e->SetX(2 * i + 1);
			e->SetY(2 * i + 4);
			gameObjects.push_back(e);
			enemyCount++;
		}
		waves++;
		
	}
	if (waves == MAXWAVES && boss < MAXBOSS)
	{
		Enemy* e = new Enemy(1, readInObjects[0]->GetText(), Green, Black,1000, readInObjects[1]->GetX(), readInObjects[1]->GetY());
		gameObjects.push_back(e);
		enemyCount = 1;
		boss++;
	}
	// Game over if player is dead
	if (!gameObjects[PLAYER_SUB]->GetAlive())
	{
		Game::ChangeState(MENU_STATE);
	}
}
void GameState::Render()
{
	int i = 1;
	Console::SetCursorPosition(0, 1);
	cout << (char)201;
	for (; i < Console::WindowWidth(); i++)
	{
		cout << (char)205;
	}
	cout << (char)187;
	for (i = 2; i < Console::WindowHeight() - 2; i++)
	{
		Console::SetCursorPosition(0, i);
		cout << (char)186;
	}
	for (i = 2; i < Console::WindowHeight() - 2; i++)
	{
		Console::SetCursorPosition(Console::WindowWidth(), i);
		cout << (char)186;
	}
	Console::SetCursorPosition(0, Console::WindowHeight() - 2);
	cout << (char)200;
	for (i = 1; i < Console::WindowWidth(); i++)
	{
		cout << (char)205;
	}
	cout << (char)188;
	for (i = 0; i < numofStars; i++)
	{
		stars[i].Show(0, 0);
	}

	for (i = 0; i < (int)gameObjects.Size(); i++)
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
		e->SetY(2 * i + 3);
		gameObjects.push_back(e);
		enemyCount++;
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
	info.killCount = p->GetKillCount();
	strcpy_s(info.buffer, 32, p->GetName());

	string tempLine = p->GetName();
	tempLine += " earned ";
	tempLine += to_string(p->GetScore());
	tempLine += " by Killing ";
	tempLine += to_string(p->GetKillCount());
	tempLine += " enemies on Difficulty ";
	tempLine += to_string(p->GetDiff());
	for (size_t i = 0; i < tempLine.length(); i++)
	{
		Sleep(50);
		cout << tempLine[i];
	}





	vector<PlayerInfo> scores;
	scores.push_back(info);
	fstream bout, tout;
	bout.open("scores.bin", ios_base::binary | ios_base::app | ios_base::out);
	tout.open("scores.txt", ios_base::app | ios_base::out);

	if (bout.is_open())
	{

		bout.write((char*)scores.data(), sizeof(PlayerInfo)* scores.size());

		bout.close();
	}

	char name[32] = "Number Six";
	bout.open("scores.bin", ios_base::binary | ios_base::in | ios_base::out);

	if (bout.is_open())
	{
		bout.seekp(sizeof(PlayerInfo) * 5, ios::beg);
		bout.write((char*)name, sizeof(name));
		bout.close();
	}



	if (tout.is_open())
	{
		tout << p->GetName() << "\t" << p->GetScore() << "\t" << p->GetDiff() << "\n";
		tout.close();
	}
	Sleep(1500);

	//reset player
	p->Reset();

	//delete everything except player in the gameObjects array.

	for (int i = 1; i < gameObjects.Size(); i++)
	{
		delete gameObjects[i];
		gameObjects.erase(i);
	}
	enemyCount = 0;
	

}


void GameState::ReadObFromFile()
{
	ifstream fin;
	int fg, bg, x, y, numofRI;
	fg = bg = x = y = numofRI = 0;
	char buffer[500];
	fin.open("images.txt");
	if (fin.is_open())
	{
		fin >> numofRI; //read the Object count in the first line
		for (int i = 0; i < numofRI; i++)
		{
			readInObjects.push_back(new BaseObject());
		}
		fin.ignore(LLONG_MAX, '\n');
		int i = 0;
		while (!fin.eof() && i < numofRI)
		{
			buffer[0] = '\0';
			fin.get(buffer, 500, '\t');
			readInObjects[i]->SetText(buffer);
			//fin.ignore(LLONG_MAX, '\t');
			fin >> fg;
			readInObjects[i]->SetForeGround((ConsoleColor)fg);
			fin.ignore(LLONG_MAX, '\t');
			fin >> bg;
			readInObjects[i]->SetBackGround((ConsoleColor)bg);
			fin >> x;
			readInObjects[i]->SetX(x);
			fin.ignore(LLONG_MAX, '\t');
			fin >> y;
			readInObjects[i]->SetY(y);
			fin.ignore(LLONG_MAX, '\n');
			i++;
		}
		fin.close();
	}

}

void GameState::GenerateStars()
{
	int i = 0; // give each stars a random color
	for (; i < numofStars; i++)
	{
		int fg = rand() % 16 + 1;
		int bg = rand() % 16 + 1;
		int oX = rand() % Console::WindowWidth();
		int oY = rand() % (Console::WindowHeight() - 2) + 1;
		while (fg == bg)
		{
			fg = rand() % 16 + 1;
			bg = rand() % 16 + 1;
		}
		for (int j = 0; j < i; j++)
		{
			if (oX == stars[j].oX && oY == stars[j].oY)
			{
				oX = rand() % Console::WindowWidth();
				oY = rand() % (Console::WindowHeight() - 2) + 1;
				j = 0;
			}
		}
		stars[i] = Cell<>(oX, oY, ConsoleColor(fg), ConsoleColor(bg), '*');
	}



}