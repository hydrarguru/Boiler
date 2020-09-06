#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <map>

//SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class State
{
private:
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool quit;
public:
	State(sf::RenderWindow* window);
	~State();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState() = 0;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
};