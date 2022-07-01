#pragma once
#include "State.h"
#include "GameState.h"
#include "../GUI/Button.h"
#include "../GUI/Label.h"


class MainMenuState : public State
{
private:
	//Variables
	sf::Image windowIcon;
	sf::RectangleShape background;
	sf::Font font;
	std::map<int, Button*> buttonList;
	std::map<int, Label*> labelList;
	sf::Clock dtClock;
	sf::Color bgColor;


	std::string ENGINE_FONT = "fonts/OpenSans-Regular.ttf";


	//Functions
	void InitBackground();
	void InitFont();
	void InitGUI();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	/*Functions*/
	void UpdateInput(const float& dt);
	void UpdateButtonEvent();/*Handles updating for all the buttons.*/
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
	void RenderImgui();
	void RenderGUI(sf::RenderTarget* target);/*Handles all rendering for the GUI.*/
};

