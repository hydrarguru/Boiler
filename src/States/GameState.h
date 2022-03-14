#pragma once
#include "State.h"
#include "GameState.h"
#include "GUI/Button.h"
#include "GUI/Label.h"
#include "Entity/Player.h"

class GameState : public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Font font;
	sf::Color bgColor;
	sf::Clock dtClock;
	std::map<int, Button*> buttonList;
	std::map<int, Label*> labelList;
	Player* player;

	//Functions
	void InitPlayer();

	//State Functions
	void InitBackground();
	void InitFont();
	void InitImgui();
	void InitGUI();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	/*Functions*/
	void UpdateInput(const float& dt);
	void UpdateButtonEvent();/*Handles updating for all the buttons.*/
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
	void RenderImgui();
	void RenderGUI(sf::RenderTarget* target);/*Handles all rendering for the GUI.*/
};

