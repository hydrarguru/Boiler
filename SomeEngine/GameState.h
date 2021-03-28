#pragma once
#include "State.h"
#include "Button.h"
#include "Label.h"

class GameState : public State
{
private:
	//Variables
	Player* player;
	sf::Clock dtClock;


	std::map<std::string, Label*> labels;
	std::map<std::string, Button*> buttons;
	sf::Font font;


	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();

	void initFonts();
	void initImGui();
	void initVars();
	void initGUI();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	/*Functions*/
	void RenderImGui(sf::RenderTarget* target);
	void updateInput(const float& dt);
	void updateButtons();
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
	void renderGUI(sf::RenderTarget* target);
};
