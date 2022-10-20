#pragma once
#include "State.h"
#include "../GUI/Button.h"
#include "../GUI/Label.h"
#include "MainMenuState.h"
#include <filesystem>
#include "mini.h"


class SettingsMenuState : public State
{
private:
	//Variables
	sf::Image windowIcon;
	sf::RectangleShape background;
	sf::Font font;
	sf::Clock dtClock;
	sf::Color bgColor;
	std::string ENGINE_FONT = "fonts/OpenSans-Regular.ttf";
	//std::map<int, Button*> buttonList;
	//std::map<int, Label*> labelList;
	std::string windowTitle;
	int windowWidth;
	int windowHeight;
	int vsyncEnabled;
	int fullscreenEnabled;
	int framerate;
	int antialiasing;


	//Functions
	void InitBackground();
	void InitFont();
	void InitGUI();
	void ReadSettings();
	void ApplySettings();
public:
	SettingsMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsMenuState();

	/*Functions*/
	void UpdateInput(const float& dt);
	void UpdateButtonEvent();/*Handles updating for all the buttons.*/
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
	void RenderImgui();
	void RenderGUI(sf::RenderTarget* target);/*Handles all rendering for the GUI.*/
};

