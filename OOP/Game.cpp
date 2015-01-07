#include "stdafx.h"
#include "Game.h"
#include "BaseObject.h"

Game::Game()
{
}


Game::~Game()
{
	delete[] ships;
}

void Game::Play()
{
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
}
