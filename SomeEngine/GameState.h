#pragma once
#include "State.h"

class GameState : public State
{
private:
	//Variables
	Player* player;


	sf::Clock dtClock;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();

	void initImGui();
	void initVars();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	/*Functions*/
	void RenderImGui(sf::RenderTarget* target);
	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
};
