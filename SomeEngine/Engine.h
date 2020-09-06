#pragma once
#include "GameState.h"

class Engine
{
private:
	/*Variables*/
	sf::Font _font;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Text text;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	/*Init*/
	void initWindow();
	void initState();

public:
	//Constructor - Destructor
	Engine();
	virtual ~Engine();


	//Functions
	void endApp();
	void loadFont(std::string font);

	//Update
	void UpdateDt();
	void updateSFMLEvents();
	void Update();

	//Render
	void Render();

	//Core
	void Run();
};
