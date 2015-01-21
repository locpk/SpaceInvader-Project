#include "stdafx.h"
#include "MenuState.h"
#include "Game.h"


MenuState::MenuState()
{
	menuNum = 0;
	menuStrings[0] = "Play";
	menuStrings[1] = "Options";
	menuStrings[2] = "HighScore";
	menuStrings[3] = "Exit";


	fstream fin;
	fin.open("MenuART.txt");
	if (fin.is_open())
	{
		string tempLine;
		while (fin.good())
		{
			std::getline(fin, tempLine);
			menuArt +=tempLine;
			menuArt += "\n";
		}
		fin.close();
	}
}


MenuState::~MenuState()
{
}

void MenuState::Input()
{
	if (GetAsyncKeyState(VK_RETURN) && !buttonPressed)
	{
		switch (menuNum)
		{
		case 0:
		{
			Game::ChangeState(GAME_STATE);
			break;
		}
		case 1:
		{
			Game::ChangeState(OPTION_STATE);
			break;
		}
		case 2:
		{
			Game::ChangeState(HIGHSCORE_STATE);
			break;
		}
		case 3:
			Game::ChangeState(EXIT_STATE);
			break;
		default:
			break;
		}

		buttonPressed = true;
	}

	if ((GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) && !buttonPressed)
	{
		--menuNum;
		buttonPressed = true;
	}

	if ((GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) && !buttonPressed)
	{
		++menuNum;
		buttonPressed = true;
	}

	if (menuNum < 0)
		menuNum = 3;

	if (menuNum > 3)
		menuNum = 0;
}

void MenuState::Update(int _frame)
{
	if (!GetAsyncKeyState('W') && !GetAsyncKeyState('S') && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_RETURN))
		buttonPressed = false;
}

void MenuState::Render()
{
	Console::Lock(true);
	Console::Clear();
	cout << menuArt;
	int i = 0;
	for (; i < 4; ++i)
	{
		if (menuNum == i)
		{
			Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 9, 25 + i);
			Console::ForegroundColor(Yellow);
			cout << "->";
			cout << menuStrings[i];
			Console::ResetColor();
		}
		else
		{
			Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 8, 25 + i);
			cout << menuStrings[i];
		}
			
	}
	Console::Lock(false);
}

void MenuState::Enter()
{
	System::Console::FlushKeys();
	Sleep(15);
	buttonPressed = true;
}

void MenuState::Exit()
{
	Console::FlushKeys();
}
