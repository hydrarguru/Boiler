#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class Label
{
private:
	sf::Text _labelText;
public:
	Label(float posX, float posY, std::string text, sf::Font* font, unsigned int labelSize, sf::Color labelColor, sf::Color outlineColor);
	~Label();

	//Functions
	void Render(sf::RenderTarget* target);
};

