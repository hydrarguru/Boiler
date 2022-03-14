#include "Engine.h"

void Engine::InitWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "asdasd", sf::Style::Resize);
	font.loadFromFile("OpenSans-Regular.ttf");
	buttons[1] = new Button(100.f, 100.f, 100.f, 50.f, &font, "Hello!", sf::Color::Blue, sf::Color::Green, sf::Color::Yellow);
	labels[1] = new Label(200, 300, "Label", &font, 50);
}

void Engine::InitState()
{
	DebugLog("Init State");
	states.push(new GameState(window, &states));
}

Engine::Engine()
{
	InitWindow();
	//InitState();
}

Engine::~Engine()
{
	delete window;
	while (!states.empty())
	{
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
	//buttons[1]->Update(mouseposview);
	if (!states.empty()) /*Updates state*/
	{
		states.top()->Update(dt);
		if (states.top()->GetQuit())
		{
			states.top()->EndState();
			states.pop();
		}
	}
}

void Engine::Render()
{
	window->clear(sf::Color::Black);
	buttons[1]->Render(window);
	labels[1]->Render(window);
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