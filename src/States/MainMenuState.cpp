﻿#include "MainMenuState.h"



MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->InitFont();
	this->InitBackground();
	this->InitGUI();
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::InitBackground()
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile(ENGINE_FONT))
	{
		throw("ERROR::MainMenuState::COULD NOT LOAD FONT");
	}
	std::cout << "MainMenuState::Loaded Fonts" << std::endl;
}

void MainMenuState::InitGUI()
{
	#pragma region Buttons
	buttonList[1] = new Button(10, 10, 200, 75,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttonList[2] = new Button(10, 90, 200, 75,
		&this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttonList[3] = new Button(10, 170, 200, 75,
		&this->font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	#pragma endregion
}

void MainMenuState::UpdateInput(const float& dt)
{
	/*handling inputs and stuff*/
}

void MainMenuState::UpdateButtonEvent()
{
	for (auto &button : buttonList)
		button.second->Update(this->mousePosView);

	if (this->buttonList[1]->IsPressed())
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));

	if (this->buttonList[2]->IsPressed())
		this->states->push(new SettingsMenuState(this->window, this->supportedKeys, this->states));

	if (this->buttonList[3]->IsPressed())
		this->EndState();
}

void MainMenuState::RenderGUI(sf::RenderTarget* target)
{
	for (auto& button : this->buttonList)
		button.second->Render(target);

	for (auto& label : this->labelList)
		label.second->Render(target);
}

void MainMenuState::RenderImgui()
{
	ImGui::ShowDemoWindow();
	ImGui::SFML::Render(*this->window);
}

void MainMenuState::Update(const float& dt)
{
	ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->UpdateButtonEvent();
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	RenderGUI(target);
	RenderImgui(); //ensures imgui windows are rendered on top of of other gui elements.
}