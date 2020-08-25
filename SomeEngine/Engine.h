#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

//SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Engine
{
private:
	sf::Font font;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	void initWindow(const int WIDTH, const int HEIGHT, const std::string windowTitle);

public:
	Engine();
	virtual ~Engine();


	//Functions
	void updateSFMLEvents();
	void Update();
	void Render();
	void Run();
	void loadFont();
};
