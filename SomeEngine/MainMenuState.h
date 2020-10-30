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
	sf::Clock dtClock;

	bool demoWindow = true;

	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	//Functions
	void initImGui();
	void initVars();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	/*Functions*/
	void endState();

	void updateInput(const float& dt);

	/*
	Handles updating for all the buttons.
	*/
	void updateButtons();

	void Update(const float& dt);
	void RenderImGUI(sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);
	/*
	Handles all rendering for the buttons.
	*/
	void renderButtons(sf::RenderTarget* target);
};

