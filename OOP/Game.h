#pragma once

class BaseObject;

class Game
{
private:
#pragma region Lab1
#if 0
	int num;
	BaseObject* ships;
#endif
#pragma endregion
	int frame = 0;
	bool play = true;
	BaseObject* objects;
public:
	Game();

	~Game();

	void Play();
	void Input();
	void Update();
	void Render();

};

