#pragma once
#include "GameState.h"
#include "Button.h"
#include "Label.h"

class MainMenuState : public State
{
private:
	//Variables
	sf::Image windowIcon;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	bool showBackground = false;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Label*> labels;
	sf::Clock dtClock;
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };
	bool SHOW_MENU = true;
	const char* window_resolution[2] = { "1920 x 1080", "1280 x 720" };

	//Functions
	void InitImGui();
	void InitBackground();
	void InitFont();
	void InitKeybinds();
	void InitGUI();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	/*Functions*/
	void UpdateInput(const float& dt);
	void UpdateButtons();/*Handles updating for all the buttons.*/
	void Update(const float& dt);
	void RenderImGUI(sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);
	void RenderGUI(sf::RenderTarget* target);/*Handles all rendering for the GUI.*/
};

