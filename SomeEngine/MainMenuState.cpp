#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) : State(window, supportedKeys)
{
	this->initFonts();
	this->initKeybinds();

	this->gamestate_btn = new Button(100, 100, 200, 75, &this->font, "New Game", sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan);

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

MainMenuState::~MainMenuState()
{
	delete this->gamestate_btn;
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("segoeui.ttf"))
	{
		throw("ERROR::MainMenuState::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();


	this->keybinds["QUIT"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState" << std::endl;
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::Update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->gamestate_btn->Update(this->mousePosView);

	system("cls");
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->gamestate_btn->Render(target);
}