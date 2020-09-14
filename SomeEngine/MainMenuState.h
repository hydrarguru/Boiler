#pragma once
#include "GameState.h"


class MainMenuState : public State
{
private:
	//Variables
	sf::RectangleShape background;

	//Functions
	void initKeybinds();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	/*Functions*/
	void endState();

	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
};
