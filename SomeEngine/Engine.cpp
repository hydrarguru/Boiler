#include "Engine.h"

void Engine::initWindow()
{
	std::ifstream ifs("window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string windowTitle = "";
	sf::VideoMode windowBounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;

	unsigned framerateLimit = 60;
	bool vsyncEnabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, windowTitle);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> fullscreen;
		ifs >> framerateLimit;
		ifs >> vsyncEnabled;
		ifs >> antialiasing_level;
	}
	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if (this->fullscreen)
		this->window = new sf::RenderWindow(windowBounds, windowTitle, sf::Style::Fullscreen, this->windowSettings);
	else
		this->window = new sf::RenderWindow(windowBounds, windowTitle, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	
	this->window->setFramerateLimit(framerateLimit);
	this->window->setVerticalSyncEnabled(vsyncEnabled);
}

void Engine::initVars()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0;
}

void Engine::initKeys()
{
	std::ifstream ifs("supported_keys.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Engine::initState()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Engine::Engine()
{
	this->initWindow();
	this->initKeys();
	this->initState();
}

Engine::~Engine()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

/*Functions*/
void Engine::UpdateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Engine::updateSFMLEvents()
{
	while (this->window->pollEvent(sfEvent)) 
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Engine::Update()
{
	this->updateSFMLEvents();
	if (!this->states.empty())
	{
		this->states.top()->Update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApp();
		this->window->close();
	}
}

void Engine::Render()
{
	this->window->clear(sf::Color::Black);
	/*Render this here*/

	if (!this->states.empty())
		this->states.top()->Render(window);
	/*Render this here*/
	this->window->display();
}

void Engine::Run()
{
	while (this->window->isOpen())
	{
		this->UpdateDt();
		this->Update();
		this->Render();
	}
}

void Engine::endApp()
{
	std::cout << "Boiler Shutdown" << std::endl;
}
