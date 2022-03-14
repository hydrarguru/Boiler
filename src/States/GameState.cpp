﻿#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	DebugLog("Entered GameState");
	this->InitFont();
	this->InitBackground();
	this->InitPlayer();
	this->InitGUI();
}

GameState::~GameState()
{

}

void GameState::InitPlayer()
{
	player = new Player(150.f, 150.f, 20, 20);
}

void GameState::InitBackground()
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

void GameState::InitFont()
{
	if (this->font.loadFromFile(ENGINE_FONT)) { DebugLog("GameState::Loaded Fonts"); }
}

void GameState::InitGUI()
{
	buttonList[1] = new Button(1000, 90, 100, 50, &font, "Hey", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
	buttonList[2] = new Button(1200, 90, 100, 50, &font, "From", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
	buttonList[3] = new Button(1400, 90, 100, 50, &font, "Gamestate", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
}

void GameState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::A)))
		this->player->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::D)))
		this->player->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::W)))
		this->player->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::S)))
		this->player->Move(dt, -1.f, 0.f);
}

void GameState::UpdateButtonEvent()
{
	for (auto& button : buttonList)
	{
		button.second->Update(this->mousePosView);
	}
}

void GameState::RenderGUI(sf::RenderTarget* target)
{
	for (auto& button : this->buttonList) { button.second->Render(target); }
	
}

void GameState::Update(const float& dt)
{
	//ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	//this->player->Update(dt);
	this->UpdateButtonEvent();
}


void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	//this->player->Render(target);
	this->RenderGUI(target);
}