#pragma once
class BaseObject;
#define NUMOFGO 2 // number of game objects
class Game
{
private:
#pragma region Lab1
#if 0
	int num = 0;
	BaseObject* ships;
#endif
#pragma endregion
	int frame = 0;
	bool play = true;

	int numofRI = 0; //number of read in objects
	BaseObject* readinObjects;
	static BaseObject* gameObjects[NUMOFGO];
public:
	Game();

	~Game();

	void Play();
	void Input();
	void Update(int _frame);
	void Render();

	static BaseObject** GetObjects() { return gameObjects; }
};

