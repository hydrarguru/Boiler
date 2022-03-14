#pragma once
#include "State.h"
#include "../GUI/Button.h"
#include "../GUI/Label.h"

class GameState : public State
{
private:
	//Variables
	Player* player;
	sf::Clock dtClock;


	std::map<std::string, Button*> buttons;
	sf::Font font;


	//Functions
	void InitTextures();
	void InitPlayer();

	void InitFonts();
	//void InitImGui();
	void InitVariables();
	void InitGUI();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	/*Functions*/
	//void RenderImGui(sf::RenderTarget* target);
	void UpdateInput(const float& dt);
	void UpdateButtons();
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
	void RenderGUI(sf::RenderTarget* target);
};
