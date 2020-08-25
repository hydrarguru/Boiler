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
public:
	State(sf::RenderWindow* window);
	~State();

	virtual void endState() = 0;

	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
};