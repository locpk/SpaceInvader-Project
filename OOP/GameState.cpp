#include "stdafx.h"
#include "GameState.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"

BaseObject* GameState::gameObjects[NUMOFGO];


GameState::GameState()
{
	readinObjects = nullptr;
	gameObjects[0] = nullptr;
	gameObjects[1] = nullptr;


	
	
}


GameState::~GameState()
{
	int i = 0;
	for (; i < NUMOFGO; i++)
	{
		delete gameObjects[i];
	}
	delete[] readinObjects;
}

void GameState::Input()
{
	int i = 0;
	for (; i < 2; i++)
	{
		gameObjects[i]->Input();
	}
}
void GameState::Update(int _frame)
{
	int i = 0;
	for (; i < 2; i++)
	{
		gameObjects[i]->Update(_frame);
	}
}
void GameState::Render()
{
	int i = 0;
	for (; i < 2; i++)
	{
		gameObjects[i]->Render();
	}
}
	 
void GameState::Enter()
{
	Console::Clear();

	ifstream fin;
	int fg, bg, i;
	fg = bg = i = 0;
	char buffer[50];
	fin.open("lab1.txt");
	if (fin.is_open())
	{
		fin >> numofRI;

		readinObjects = new BaseObject[numofRI];
		int i = 0;
		fin.ignore(LLONG_MAX, '\n');

		while (!fin.eof() && i < numofRI)
		{

			fin.get(buffer, sizeof buffer, '\t');
			readinObjects[i].SetText(buffer);
			//fin.ignore(LLONG_MAX, '\t');
			fin >> fg;
			readinObjects[i].SetForeGround((ConsoleColor)fg);
			fin.ignore(LLONG_MAX, '\t');
			fin >> bg;
			readinObjects[i].SetBackGround((ConsoleColor)bg);
			fin.ignore(LLONG_MAX, '\n');
			i++;
		}
		i = 0;
		fin.close();
	}

	for (; i < numofRI; i++)
	{
		cout << i + 1 << ": " << endl;
		Console::ForegroundColor(Cyan);
		cout << readinObjects[i].GetText() << endl;
		Console::ResetColor();
	}
	int choice = 0;
	cout << "Which one would you like your enemy to be?" << endl;
	for (;;)
	{

		if (cin >> choice && choice > 0 && choice <= numofRI)
		{
			break;
		}
		cout << "Try again!" << endl;
		cin.clear();
		cin.ignore(LLONG_MAX, '\n');
	}
	gameObjects[1] = new Enemy(2,
		readinObjects[choice - 1].GetText(), readinObjects[choice - 1].GetForeGround(), readinObjects[choice - 1].GetBackGround(),
		Console::WindowWidth() >> 1, 2);
	choice = 0;
	cout << "Which one would you like to be?" << endl;
	for (;;)
	{

		if (cin >> choice && choice > 0 && choice <= numofRI)
		{
			break;
		}
		cout << "Try again!" << endl;
		cin.clear();
		cin.ignore(LLONG_MAX, '\n');
	}
	cout << "What should I call you?" << endl;
	char name[32];
	for (;;)
	{

		if (cin >> name)
		{
			break;
		}
		cout << "Try again!" << endl;
		cin.clear();
		cin.sync();
	}

	gameObjects[0] = new Player(name, 0, 0
		, readinObjects[choice - 1].GetText(), readinObjects[choice - 1].GetForeGround(), readinObjects[choice - 1].GetBackGround(),
		Console::WindowWidth() >> 1, Console::WindowHeight() >> 1);

	//save player's choices to file
	ofstream fout;
	fout.open("lab3.txt");
	if (fout.is_open())
	{
		fout << NUMOFGO << "\n";
		int i = 0;
		for (; i < NUMOFGO; ++i)
		{
			fout << gameObjects[i]->GetText() << '\t' << gameObjects[i]->GetForeGround() << '\t' << gameObjects[i]->GetBackGround()
				<< '\t' << gameObjects[i]->GetX() << '\t' << gameObjects[i]->GetY()
				<< '\n';
		}

		fout.close();
	}
}
void GameState::Exit()
{

}