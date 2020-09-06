#pragma once
#include "State.h"

class GameState : public State
{
private:
	Entity Player;

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	/*Functions*/
	void endState();
	void updateKeybinds(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
};
