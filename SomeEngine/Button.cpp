#include "Button.h"

Button::Button(float x, float y,
	float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->buttonShape.setSize(sf::Vector2f(width, height));

	this->buttonfont = font;
	this->buttonText.setFont(*this->buttonfont);
	this->buttonText.setString(text);
	this->buttonText.setFillColor(sf::Color::White);
	this->buttonText.setCharacterSize(16);
	this->buttonText.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->buttonText.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->buttonText.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->buttonShape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}



void Button::Update(const sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE; //Idle State


	if (this->buttonShape.getGlobalBounds().contains(mousePos))	//Hover State
	{
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //Pressed State
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->buttonShape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->buttonShape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->buttonShape.setFillColor(this->activeColor);
		break;
	default:
		this->buttonShape.setFillColor(sf::Color::Red);
		break;
	}

}

void Button::Render(sf::RenderTarget* target)
{
	target->draw(this->buttonShape);
	target->draw(this->buttonText);
}
