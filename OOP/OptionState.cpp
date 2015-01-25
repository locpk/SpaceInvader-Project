#include "stdafx.h"
#include "OptionState.h"
#include "Game.h"

OptionState::OptionState()
{
	menuNum = 0;
	menuStrings.resize(3);
	menuStrings[0] = "Enemy Number: ";
	menuStrings[1] = "Difficulty: ";
	menuStrings[2] = "Exit";
}


OptionState::~OptionState()
{
}

void OptionState::Input()
{

	if (GetAsyncKeyState(VK_RETURN) && !buttonPressed)
	{
		switch (menuNum)
		{
		case 0:
		{
			++enemyNum;
			if (enemyNum > 5)
			{
				enemyNum = 1;
			}

			break;
		}
		case 1:
		{
			++diff;
			if (diff > 10)
			{
				diff = 1;
			}
			break;
		}
		case 2:
		{
			Game::ChangeState(MENU_STATE);
			break;
		}
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
		menuNum = 2;

	if (menuNum > 2)
		menuNum = 0;
}
void OptionState::Update(int _frame)
{
	if (!GetAsyncKeyState('W') && !GetAsyncKeyState('S') && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_RETURN))
		buttonPressed = false;
}
void OptionState::Render()
{
	int i = 0;
	for (; i < 3; ++i)
	{
		if (menuNum == i)
		{
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 9, 20 + i);
			Console::ForegroundColor(Yellow);
			cout << "->";
			cout << menuStrings[i];
			Console::ResetColor();
		}
		else
		{
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 8, 20 + i);
			cout << menuStrings[i];
		}

		Console::ForegroundColor(Red);
		if (i == 0)
			cout << enemyNum;
		else if (i == 1)
			cout << diff;
		Console::ResetColor();
	}
}
void OptionState::Enter()
{
	enemyNum = diff = 1;
	Console::FlushKeys();
	Sleep(100);
}
void OptionState::Exit()
{
	GetInfo().diff = diff;
	GetInfo().enemyNum = enemyNum;
}
