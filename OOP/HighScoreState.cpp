#include "stdafx.h"
#include "HighScoreState.h"
#include "Game.h"
#include "Player.h"

bool ByScoreDes(PlayerInfo i, PlayerInfo j) { return (i.score > j.score); }
bool ByNameAsc(PlayerInfo const& _l, PlayerInfo const& _r){ return strcmp(_l.buffer, _r.buffer) < 0; }
bool ByDiffDes(PlayerInfo const& _l, PlayerInfo const& _r){ return _l.diff > _r.diff; }

void ShowHighScore(PlayerInfo const& _info)
{
	Console::SetCursorPosition((Console::WindowWidth() >> 1) - 15, Console::CursorTop() + 1);
	cout << _info;
}

HighScoreState::HighScoreState()
{
	menuNum = 0;
	menuStrings[0] = "By name, ascending";
	menuStrings[1] = "By name, descending";
	menuStrings[2] = "By difficulty, descending";
	menuStrings[3] = "By score, descending";
	menuStrings[4] = "Save As";
	menuStrings[5] = "Exit";
}


HighScoreState::~HighScoreState()
{
}

void HighScoreState::Input()
{
	if (GetAsyncKeyState(VK_RETURN) && !buttonPressed)
	{
		switch (menuNum)
		{
		case 0:
		{
			std::sort(inScores.begin(), inScores.end(), ByNameAsc);
			showScore = true;
			break;
		}
		case 1:
		{
			std::sort(inScores.begin(), inScores.end(), operator>);
			showScore = true;
			break;
		}
		case 2:
		{
			std::sort(inScores.begin(), inScores.end(), ByDiffDes);
			showScore = true;
			break;
		}
		case 3:
			std::sort(inScores.begin(), inScores.end(), ByScoreDes);
			showScore = true;
			break;
		case 4:
			SaveAs();
			break;
		case 5:
			Game::ChangeState(MENU_STATE);
			break;
		default:
			break;
		}
		buttonPressed = true;

	}

	if (GetAsyncKeyState(VK_ESCAPE) && !buttonPressed)
	{
		showScore = false;
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
		menuNum = 5;

	if (menuNum > 5)
		menuNum = 0;

}

void HighScoreState::Update(int _frame)
{
	if (!GetAsyncKeyState('W') && !GetAsyncKeyState('S') && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_ESCAPE))
		buttonPressed = false;
}
void HighScoreState::Render()
{
	if (showScore)
	{
		Console::Clear();
		for_each(inScores.begin(), inScores.end(), ShowHighScore);
		Console::SetCursorPosition((Console::WindowWidth() >> 1) - 15, Console::CursorTop() + 1);
		Console::ForegroundColor(Red);
		cout << "Press ESC to Return.";
		Console::ResetColor();
	}
	else
	{
		Console::Lock(true);
		Console::Clear();
		int i = 0;
		for (; i <= 5; ++i)
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
	
}
void HighScoreState::Enter()
{
	Console::FlushKeys();
	Read();
	Sleep(100);
}
void HighScoreState::Exit()
{

}

void HighScoreState::Read()
{
	fstream bin;
	bin.open("scores.bin", ios_base::binary | ios_base::in);

	if (bin.is_open())
	{
		bin.seekg(0, ios_base::end);
		int count = (int)bin.tellg();
		bin.seekg(0, ios_base::beg);
		count /= sizeof(PlayerInfo);

		/*int i = 0;
		for (; i < count; ++i)
		{
		PlayerInfo tempInfo;
		bin.read((char*)&tempInfo, sizeof(PlayerInfo));

		inScores.push_back(tempInfo);
		}*/

		inScores.resize(count);

		bin.read((char*)inScores.data(), sizeof(PlayerInfo) * count);
		bin.close();
	}
}

void HighScoreState::SaveAs()
{
	Console::Clear();

	string fileName = "HighScore";
	int entries = 0;
	cout << "Give a name to the file: ";
	cin >> fileName;
	cin.clear();
	cin.ignore(LLONG_MAX, '\n');
	fileName += ".txt";
	cout << "How many entries do you want to save?";
	for (;;)
	{
		if (cin >> entries && entries < (int)inScores.size() && entries >= 0)
			break;
		cin.clear();
		cin.ignore(LLONG_MAX, '\n');
	}

	ofstream fout;
	fout.open(fileName);
	while (fout.is_open())
	{
		for (int i = 0; i < entries; i++)
		{
			fout << inScores[i];
		}
		fout.close();
	}
}

