#pragma once


class BaseObject;
class BaseState;

/** @brief STATE_TYPES enum as a state machine indication.
*/
enum STATE_TYPES { MENU_STATE = 0, GAME_STATE, OPTION_STATE, HIGHSCORE_STATE ,EXIT_STATE };


/** @brief Game class.
*	@author Junshu Chen
*	@date Jan 2015
*/
class Game
{
private:
	int frame = 0;
	static char cheats;
	static bool play;
	static BaseState* currentState;
	static vector<BaseState*> states;
public:
	/**
	* Default Constructor.
	*/
	Game();
	/**
	* Default Destructor.
	*/
	~Game();

	/**
	* Main game loop calls Input, Update and Render functions.
	*/
	void Play();

	/**
	* Call current state's Input function.
	*/
	void Input();

	/**
	* Call current state's Update function.
	*@param _frame global frame count.
	*/
	void Update(int _frame);

	/**
	* Call current state's Render function.
	*/
	void Render();

	/**
	* Change state based on [in]
	*@param _state the state will be switched to.
	*/
	static void ChangeState(STATE_TYPES _state);

	/**
	* Toggle the Game::play by passing in boolean.
	* @param _play 
	*/
	static void SetPlay(const bool _play) { play = _play; }

	static char& GetCheats() { return cheats; }
};

