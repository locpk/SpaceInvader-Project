#include "stdafx.h"
#include "HighScoreState.h"
#include "Game.h"
#include "Player.h"

HighScoreState::HighScoreState()
{
}


HighScoreState::~HighScoreState()
{
}

void HighScoreState::Input()
{
	if (GetAsyncKeyState(VK_RETURN) && !buttonPressed)
	{
		buttonPressed = true;
		Game::ChangeState(MENU_STATE);
	}
}
void HighScoreState::Update(int _frame)
{
	if (!GetAsyncKeyState(VK_RETURN))
	{
		buttonPressed = false;
	}
}
void HighScoreState::Render()
{
	Console::Clear();
	Console::SetCursorPosition((Console::WindowWidth() >> 1) - 15, 0);
	for (int i = 0; i < (int)inScores.size(); i++)
	{
		Console::SetCursorPosition((Console::WindowWidth() >> 1) - 15, Console::CursorTop() + 1);
		cout << inScores[i].buffer << " on " << inScores[i].diff << "Killed: " << inScores[i].killCount << " Got: "<< inScores[i].score << "\n";
	}
}
void HighScoreState::Enter()
{
	Console::FlushKeys();

	fstream bin;
	bin.open("scores.bin", ios_base::binary | ios_base::in);

	if (bin.is_open())
	{
		bin.seekg(0, ios_base::end);
		int count = (int)bin.tellg();
		bin.seekg(0, ios_base::beg);
		count /= sizeof(PlayerInfo);

		

		//Two ways we can do this
		

		//Looping method


		int i = 0;
		for (; i < count; ++i)
		{
		PlayerInfo tempInfo;
		bin.read((char*)&tempInfo, sizeof(PlayerInfo));

		inScores.push_back(tempInfo);
		}
		

		//Non-looping, all at once call
		/*inScores.resize(count);

		bin.read((char*)inScores.data(), sizeof(PlayerInfo) * count);*/
		bin.close();
	}
}
void HighScoreState::Exit()
{

}