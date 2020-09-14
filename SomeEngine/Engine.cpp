#include "Engine.h"

void Engine::initWindow()
{
	loadFont("segoeui.ttf");
	text.setFont(_font);
	text.setPosition(sf::Vector2f(640, 0));
	text.setString("Boiler Engine");

	std::ifstream ifs("window.ini");
	std::string windowTitle = "";
	sf::VideoMode windowBounds(1280,720);
	unsigned framerateLimit = 60;
	bool vsyncEnabled = false;
	if (ifs.is_open())
	{
		std::getline(ifs, windowTitle);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> framerateLimit;
		ifs >> vsyncEnabled;
	}
	ifs.close();

	this->window = new sf::RenderWindow(windowBounds, windowTitle);
	this->window->setFramerateLimit(framerateLimit);
	this->window->setVerticalSyncEnabled(vsyncEnabled);
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
	this->states.push(new GameState(this->window, &this->supportedKeys));
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
	this->window->draw(text);
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

void Engine::loadFont(std::string font)
{
	if (_font.loadFromFile(font))
	{
		std::cout << "Font loaded: " << font << std::endl;
	}
	else
	{
		std::cout << "Font not loaded!" << std::endl;
	}
}
