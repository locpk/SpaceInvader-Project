#include "stdafx.h"
#include "Game.h"
#include "BaseObject.h"
#include "Player.h"
Game::Game()
{
	System::Console::SetBufferSize(80, 25);
	System::Console::SetWindowSize(80, 25);
	System::Console::EOLWrap(false);
	objects = nullptr;
	objects = new Player("pig", 0, 0, "lol\nlol\nlol", White, Black, Console::WindowWidth() >> 1, Console::WindowHeight() >> 1);
}


Game::~Game()
{
#pragma region Lab1
#if 0
	delete[] ships;
#endif
#pragma endregion
	delete objects;

}

void Game::Play()
{
#pragma region Lab1 
#if 0
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
		fout << card.GetText() << '\t' << card.GetX() << '\t' << card.GetY() << '\n';
		fout << dice.GetText() << '\t' << dice.GetX() << '\t' << dice.GetY() << '\n';
		for (; i < num; ++i)
		{
			fout << ships[i].GetText() << '\t' << ships[i].GetX() << '\t' << ships[i].GetY() << '\n';
		}

		fout.close();
	}
#endif
#pragma endregion


	/*for (; play;frame++)
	{
		Input();
		Update();
		Render();
		Sleep(10);
	}*/

	ifstream fin;
	int num = 0;
	int x, y,i;
	x = y = i = 0;
	char buffer[50];
	fin.open("lab1.txt");
	if (fin.is_open())
	{
		fin >> num;
		fin.ignore(LLONG_MAX, '\n');

		while (!fin.eof())
		{
			fin.get(buffer,sizeof buffer, '\t');
			//fin.ignore(LLONG_MAX, '\t');
			fin >> x;
			fin.ignore(LLONG_MAX, '\t');
			fin >> y;
			fin.ignore(LLONG_MAX, '\n');
			cout << buffer << "\t" << x << "\t" << y << endl;
		}
		fin.close();
	}



}

void Game::Input()
{
	if (GetAsyncKeyState(VK_ESCAPE))
		play = false;
	objects->Input();
}
void Game::Update()
{

}
void Game::Render()
{
	System::Console::Lock(true);
	System::Console::Clear();
	objects->Render();

	System::Console::Lock(false);
}
