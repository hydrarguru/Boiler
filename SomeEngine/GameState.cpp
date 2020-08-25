#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{

}

GameState::~GameState()
{

}

void GameState::endState()
{

}

void GameState::Update(const float& dt)
{
	std::cout << "Hello from GameState" << std::endl;
}

void GameState::Render(sf::RenderTarget* target)
{

}
