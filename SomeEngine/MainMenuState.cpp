#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
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
	std::ifstream ifs("mainmenustate_keybinds.ini");
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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(10, 10, 200, 75,
		&this->font, "New Game",
		sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan);

	this->buttons["EXIT_STATE"] = new Button(10, 80, 200, 75,
		&this->font, "QUIT",
		sf::Color::Green, sf::Color::Magenta, sf::Color::Cyan);
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState" << std::endl;
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->Update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed()) //Exit the Application
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EXIT_STATE"]->isPressed()) //Exit the Application
	{
		this->quit = true;
	}
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void MainMenuState::Update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderButtons(target);
}

