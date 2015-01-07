#pragma once

class BaseObject;

class Game
{
private:
	int num;
	BaseObject* ships;
public:
	Game();

	~Game();

	void Play();
};

