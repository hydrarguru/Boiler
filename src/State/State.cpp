#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->quit = false;
	this->states = states;
}

State::~State()
{

}

const bool& State::GetQuit() const
{
	return quit;
}

void State::EndState()
{
	quit = true;
}

void State::UpdateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}