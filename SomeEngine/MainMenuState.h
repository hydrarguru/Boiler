#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;
	sf::Clock dtClock;

	bool SHOW_MOUSE_POS_DEBUG = false;

	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	//Functions
	void initImGui();
	void initBackground();
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

	
	void updateButtons();/*Handles updating for all the buttons.*/

	void Update(const float& dt);
	void RenderImGUI(sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);
	
	void renderButtons(sf::RenderTarget* target);/*Handles all rendering for the buttons.*/
};

