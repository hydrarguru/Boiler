#include "Engine.h"

void Engine::InitWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(window_height, window_width), windowTitle, sf::Style::Resize);
	this->window->setFramerateLimit(framerate);
}

void Engine::InitVariables()
{
	this->window = nullptr;
	this->dt = 0;
}

void Engine::InitState()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Engine::Engine()
{
	InitWindow();
	InitState();
}

Engine::~Engine()
{
	delete this->window;
	while (!this->states.empty())
	{
		//delete this->states.top();
		this->states.pop();
	}
}

/*Functions*/
void Engine::UpdateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Engine::UpdateSFMLEvents()
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
	this->UpdateSFMLEvents();
	if (!this->states.empty())
	{
		this->states.top()->Update(this->dt);

		if (this->states.top()->GetQuit())
		{
			this->states.top()->EndState();
			//delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->window->close();
	}
}

void Engine::Render()
{
	this->window->clear(sf::Color::Black);
	if (!this->states.empty())
		this->states.top()->Render(window);
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
