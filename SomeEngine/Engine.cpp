#include "Engine.h"

void Engine::initWindow()
{
	loadFont();
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

void Engine::initState()
{
	this->states.push(new GameState(this->window));
}

Engine::Engine()
{
	initWindow();
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

void Engine::loadFont()
{
	std::string segoue = "segoeui.ttf";
	if (font.loadFromFile(segoue))
	{
		std::cout << "Font loaded: " << segoue << std::endl;
	}
	else
	{
		std::cout << "Font not loaded!" << std::endl;
	}
}

void Engine::endApp()
{
	std::cout << "Boiler Shutdown" << std::endl;
}
