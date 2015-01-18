#include "stdafx.h"
#include "Game.h"
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
#include "BaseState.h"
#include "GameState.h"
#include "MenuState.h"

#pragma region Lab2
#if LAB2
BaseObject* Game::gameObjects[NUMOFGO];
#endif
#pragma endregion


BaseState* Game::currentState = NULL;
vector<BaseState*> Game::states;

Game::Game()
{
	System::Console::SetBufferSize(200, 50);
	System::Console::SetWindowSize(200, 50);
	System::Console::EOLWrap(false);

#pragma region Lab2
#if LAB2
	readinObjects = nullptr;
	gameObjects[0] = nullptr;
	gameObjects[1] = nullptr;
#endif
#pragma endregion

	//Set up the states
	states.push_back(new MenuState());
	states.push_back(new GameState());
}


Game::~Game()
{

#pragma region Lab1
#if LAB1
	delete[] ships;
#endif
#pragma endregion
#pragma region Lab2
#if LAB2
	int i = 0;
	for (; i < NUMOFGO; i++)
	{
		delete gameObjects[i];
	}
	delete[] readinObjects;
#endif
#pragma endregion
	int i = 0;
	for (; i < (int)states.size(); i++)
	{
		delete states[i];
	}
	
}

void Game::Play()
{
#pragma region Lab1 
#if LAB1
	BaseObject card("+---+\n|A  |\n| \x3 |\n|  A|\n+---+",White,Black, 12, 15), // Try \x3 instead of H
		dice("* *\n * \n* *", White, Black, 0, 15);
	cout << "Before:\n";
	card.Render(); cout << '\n';
	dice.Render(); cout << '\n';
	BaseObject temp = card;
	card = dice;
	dice = temp;
	cout << "After:\n";
	card.Render(); cout << '\n';
	dice.Render(); cout << '\n';

	BaseObject ship("|O|", White, Black, 8, 0);

	cout << "How many ships do u want? _\b";
	while (!(cin >> num) || num < 0)
	{
		cout << "How many ships do u want? _\b";
		cin.clear();
		cin.sync();
	}
	Console::Clear();
	ships = new BaseObject[num];
	/*Console::SetBufferSize(80, 30);
	Console::SetWindowSize(80, 30);*/
	for (int i = 0; i < num; i++)
	{

		ships[i] = ship;
		if (0 != i)
		{
			if (Console::WindowWidth() - (ships[i - 1].GetX() + 3) >= 3)
			{
				ships[i].SetX(ships[i - 1].GetX() + 3);
				ships[i].SetY(ships[i - 1].GetY());
			}

			else
			{
				ships[i].SetX(0);
				ships[i].SetY(ships[i - 1].GetY() + 1);
			}
		}

	}

	for (int i = 0; i < num; i++)
	{
		ships[i].Render();
	}

	ofstream fout;
	fout.open("lab1.txt");
	if (fout.is_open())
	{
		fout << num + 2 << "\n";
		int i = 0;
		fout << card.GetText() << '\t' << card.GetForeGround() << '\t' << card.GetBackGround() << '\n';
		fout << dice.GetText() << '\t' << dice.GetForeGround() << '\t' << dice.GetBackGround() << '\n';
		for (; i < num; ++i)
		{
			fout << ships[i].GetText() << '\t' << ships[i].GetForeGround() << '\t' << ships[i].GetBackGround() << '\n';
		}

		fout.close();
	}
	
	system("pause");
	Console::Clear();
#endif
#pragma endregion
#pragma region Lab2
#if LAB2

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
	fout.open("lab2.txt");
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


	
#endif
#pragma endregion


	ChangeState(MENU_STATE);

	for (; play; ++frame)
	{
		Input();
		Update(frame);
		Render();
		Sleep(30);
	}



}

void Game::Input()
{

	currentState->Input();

	if (GetAsyncKeyState(VK_ESCAPE))
		play = false;
#pragma region Lab2
#if LAB2
	int i = 0;
	for (; i < 2; i++)
	{
		gameObjects[i]->Input();
	}
#endif
#pragma endregion
	

}
void Game::Update(int _frame)
{
#pragma region Lab2
#if LAB2
	int i = 0;
	for (; i < 2; i++)
	{
		gameObjects[i]->Update(_frame);
	}
#endif
#pragma endregion 
	currentState->Update(_frame);
}
void Game::Render()
{
	System::Console::Lock(true);
	System::Console::Clear();
#pragma region Lab2
#if LAB2
	int i = 0;
	for (; i < 2; i++)
	{
		gameObjects[i]->Render();
	}
#endif
#pragma endregion
	currentState->Render();

	System::Console::Lock(false);
}


void Game::ChangeState(STATE_TYPES _state)
{
	if (currentState)
		currentState->Exit();

	currentState = states[_state];
	currentState->Enter();
}
