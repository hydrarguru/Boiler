#pragma once
#include "State.h"

class GameState : public State
{
private:
	//Variables
	Entity Player;

	sf::Clock dtClock;
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	//Functions
	void initKeybinds();
	void initImGui();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	/*Functions*/
	void RenderImGui(sf::RenderTarget* target);
	void endState();
	void updateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
};
