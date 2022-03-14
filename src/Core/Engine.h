#pragma once
#include "base.h"
#include "State/State.h"
#include "State/GameState.h"
#include "GUI/Button.h"
#include "GUI/Label.h"

class Engine
{
private:
	/*Variables*/
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;
	std::stack<State*> states;
	std::map<int, Button*> buttons;
	std::map<int, Label*> labels;
	sf::Font font;


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
