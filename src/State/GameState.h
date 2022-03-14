#pragma once
#include "State.h"
#include "GUI/Button.h"

class GameState : public State
{
private:
	//Variables
	sf::Clock dtClock;
	sf::Font font;
	std::map<int, Button*> buttonList;

	//Functions
	void InitTextures();
	void InitFonts();
	void InitGUI();
public:
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	/*Functions*/
	void UpdateInput(const float& dt);
	void UpdateButtons();
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
	void RenderGUI(sf::RenderTarget* target);
};