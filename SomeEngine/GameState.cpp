#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{

}

GameState::~GameState()
{

}

void GameState::endState()
{
	std::cout << "Ending GameState" << std::endl;
}

void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void GameState::Update(const float& dt)
{
	this->updateKeybinds(dt);
	this->Player.Update(dt);
	
}

void GameState::Render(sf::RenderTarget* target)
{
	this->Player.Render(this->window);
}
