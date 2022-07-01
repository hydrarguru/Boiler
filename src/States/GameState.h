#pragma once
#include "GameState.h"
#include "State.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "GUI/Button.h"
#include "GUI/Label.h"
#include "Entity/Player.h"

#include <imgui-SFML.h>
#include <imgui.h>


class GameState : public State
{
private:
	//Variables
	sf::RectangleShape m_background;
	sf::Font m_font;
	sf::Color m_bgColor;
	sf::Clock m_dtClock;
	std::map<int, Button*> m_buttonList;
	std::map<int, Label*> m_labelList;
	Player* m_player;


	std::string ENGINE_FONT = "fonts/OpenSans-Regular.ttf";

	//Functions
	void InitPlayer();

	//State Functions
	void InitFont();
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

