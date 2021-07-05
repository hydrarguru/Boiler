#pragma once
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

enum button_states{BTN_IDLE = 0, BTN_HOVER = 1, BTN_ACTIVE = 2};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape buttonShape;
	sf::Font* buttonfont;
	sf::Text buttonText;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(
		float x,
		float y,
		float width,
		float height,
		sf::Font* font,
		std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Accessors
	const bool IsPressed() const;


	//Functions
	void Update(const sf::Vector2f mousePos);
	void Render(sf::RenderTarget* target);
};

