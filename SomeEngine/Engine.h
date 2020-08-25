#pragma once
#include "State.h"

class Engine
{
private:
	/*Variables*/
	sf::Font font;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	/*Init*/
	void initWindow();

public:
	//Constructor - Destructor
	Engine();
	virtual ~Engine();


	//Functions
	void UpdateDt();
	void updateSFMLEvents();
	void Update();
	void Render();
	void Run();
	void loadFont();
};
