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

	if (GetAsyncKeyState('W') && !buttonPressed)
	{
		--menuNum;
		buttonPressed = true;
	}

	if (GetAsyncKeyState('S') && !buttonPressed)
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
	if (!GetAsyncKeyState('W') && !GetAsyncKeyState('S') && !GetAsyncKeyState(VK_RETURN))
		buttonPressed = false;
}
void OptionState::Render()
{
	int i = 0;
	for (; i < 3; ++i)
	{
		if (menuNum == i)
		{
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 10, 10 + i);
			cout << "->";
		}
		else
			System::Console::SetCursorPosition((System::Console::WindowWidth() >> 1) - 8, 10 + i);

		cout << menuStrings[i];

		if (i == 0)
			cout << enemyNum;
		else if (i == 1)
			cout << diff;
	}
}
void OptionState::Enter()
{
	enemyNum = diff = 1;
	System::Console::FlushKeys();
	Sleep(15);
}
void OptionState::Exit()
{
	GetInfo().diff = diff;
	GetInfo().enemyNum = enemyNum;
}
