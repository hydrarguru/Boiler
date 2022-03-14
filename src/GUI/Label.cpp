#include "Label.h"

Label::Label(float posX, float posY, std::string text, sf::Font* font, unsigned int labelSize, sf::Color labelColor, sf::Color outlineColor)
{
	_labelText.setPosition(sf::Vector2f(posX, posY));
	_labelText.setFillColor(labelColor);
	_labelText.setOutlineColor(outlineColor);
	_labelText.setOutlineThickness(1.f);
	_labelText.setCharacterSize(labelSize);
	_labelText.setFont(*font);
	_labelText.setString(text);
}

Label::Label(float posX, float posY, std::string text, sf::Font* font, unsigned int labelSize)
{
	_labelText.setPosition(sf::Vector2f(posX, posY));
	_labelText.setFillColor(sf::Color::White);
	_labelText.setOutlineColor(sf::Color::Black);
	_labelText.setOutlineThickness(1.f);
	_labelText.setCharacterSize(labelSize);
	_labelText.setFont(*font);
	_labelText.setString(text);
}

Label::~Label()
{
}

void Label::Render(sf::RenderTarget* target)
{
	target->draw(_labelText);
}