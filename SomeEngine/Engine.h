#pragma once
#include "MainMenuState.h"

class Engine
{
private:
	/*Variables*/
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;


	/*Init*/
	void initWindow();
	void initKeys();
	void initState();

public:
	//Constructor - Destructor
	Engine();
	virtual ~Engine();


	//Functions
	void endApp();

	//Update
	void UpdateDt();
	void updateSFMLEvents();
	void Update();

	//Render
	void Render();

	//Core
	void Run();
};
