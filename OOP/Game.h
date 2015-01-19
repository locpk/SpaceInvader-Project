#pragma once

#define LAB1 0
#define LAB2 0

#pragma region Lab2
#if LAB2
#define NUMOFGO 2 // number of game objects
#endif
#pragma endregion

class BaseObject;
class BaseState;

enum STATE_TYPES { MENU_STATE = 0, GAME_STATE, OPTION_STATE, EXIT_STATE };

class Game
{
private:
	int frame = 0;
	static bool play;
#pragma region Lab1
#if LAB1
	int num = 0;
	BaseObject* ships;
#endif
#pragma endregion	
#pragma region Lab2
#if LAB2
	int numofRI = 0; //number of read in objects
	BaseObject* readinObjects;
	static BaseObject* gameObjects[NUMOFGO];
#endif
#pragma endregion
	static BaseState* currentState;
	static vector<BaseState*> states;
public:
	Game();
	~Game();


	void Play();
	void Input();
	void Update(int _frame);
	void Render();
#pragma region Lab2
#if LAB2
	static BaseObject** GetObjects() { return gameObjects; }
#endif
#pragma endregion
	static void ChangeState(STATE_TYPES _state);
	static void SetPlay(const bool _play) { play = _play; }
};

