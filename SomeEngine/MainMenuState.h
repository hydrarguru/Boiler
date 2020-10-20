#pragma once
#include "GameState.h"
#include "Button.h"


class MainMenuState : public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	/*Functions*/
	void endState();

	void updateInput(const float& dt);

	/*
	Handles updating for all the buttons.
	*/
	void updateButtons();

	void Update(const float& dt);

	void Render(sf::RenderTarget* target);
	/*
	Handles all rendering for the buttons.
	*/
	void renderButtons(sf::RenderTarget* target);
};

