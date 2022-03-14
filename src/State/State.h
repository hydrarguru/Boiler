#pragma once
#include "Core/base.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	//Resources
	std::map<std::string, sf::Texture> textures;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	~State();

	const bool& GetQuit() const;
	void EndState();

	virtual void UpdateMousePosition();
	virtual void UpdateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
};