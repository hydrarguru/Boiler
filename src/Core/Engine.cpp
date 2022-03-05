#include "Engine.h"

void Engine::InitWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "asdasd", sf::Style::Resize);
}

void Engine::InitState()
{
	states.push(new GameState(window, &states));
}

Engine::Engine()
{
	InitWindow();
	InitState();
}

Engine::~Engine()
{
	delete window;
	while (!states.empty())
	{
		// delete states.top();
		states.pop();
	}
}

/*Functions*/
void Engine::UpdateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Engine::UpdateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}

void Engine::Update()
{
	UpdateSFMLEvents();
	if (!states.empty())
	{
		states.top()->Update(dt);
		if (states.top()->GetQuit())
		{
			states.top()->EndState();
			// delete states.top();
			states.pop();
		}
	}
	else
	{
		window->close();
	}
}

void Engine::Render()
{
	window->clear(sf::Color::Black);
	window->display();
}

void Engine::Run()
{
	while (window->isOpen())
	{
		UpdateDt();
		Update();
		Render();
	}
}