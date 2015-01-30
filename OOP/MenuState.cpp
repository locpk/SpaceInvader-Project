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
	out = &menuArt;

	fin.open("Skulls.txt");
	if (fin.is_open())
	{
		string tempLine;
		while (fin.good())
		{
			std::getline(fin, tempLine);
			skull += tempLine;
			skull += "\n";
		}
		fin.close();
	}

	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels

	system->createSound("Black-Space-Music-Pad_ELEMENT_WSR2428603.wav", FMOD_HARDWARE, 0, &sound1);
	sound1->setMode(FMOD_LOOP_OFF);

	


}


MenuState::~MenuState()
{
	sound1->release();
	system->close();
	system->release();
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
	if (_frame % 100 == 0)
		system->playSound(FMOD_CHANNEL_FREE, sound1, false, 0);
	system->update();
	if (_frame % 10 == 0)
		
	{
		Console::ForegroundColor(Red);
		out = &skull;
	}
	if (_frame % 11 == 0)
		Console::ForegroundColor(DarkRed);
	if (_frame % 12 == 0)
		Console::ForegroundColor(Red);
	if (_frame % 20 == 0)
	{
		Console::ResetColor();
		out = &menuArt;
	}
		
}

void MenuState::Render()
{
	Console::Lock(true);
	Console::Clear();
	cout << *out;
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
