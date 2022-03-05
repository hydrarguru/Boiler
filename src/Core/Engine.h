#pragma once
#include "base.h"
#include "State/State.h"
#include "State/GameState.h"

class Engine
{
private:
	/*Variables*/
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;
	std::stack<State*> states;



	/*Init*/
	void InitWindow();
	void InitState();

public:
	//Constructor - Destructor
	Engine();
	virtual ~Engine();

	//Update
	void UpdateDt();
	void UpdateSFMLEvents();
	void Update();

	//Render
	void Render();

	//Core
	void Run();
};
