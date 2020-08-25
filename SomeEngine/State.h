#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

//SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class State
{
private:
	std::vector<sf::Texture> textures;
public:
	State();
	~State();

	virtual void Update() = 0;
	virtual void Render() = 0;
};