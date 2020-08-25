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


	this->window = new sf::RenderWindow(windowBounds, windowTitle);
	this->window->setFramerateLimit(framerateLimit);
	this->window->setVerticalSyncEnabled(vsyncEnabled);
}

Engine::Engine()
{
	initWindow();
}
Engine::~Engine()
{
	delete this->window;
}
void Engine::UpdateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
	
}
/*Functions*/
void Engine::updateSFMLEvents()
{
	while (this->window->pollEvent(sfEvent)) { if (sfEvent.type == sf::Event::Closed) { this->window->close(); } }
}
void Engine::Update()
{
	this->updateSFMLEvents();
}
void Engine::Render()
{
	this->window->clear(sf::Color::Black);
	/*Render this here*/


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
	if (font.loadFromFile("segoeui.ttf"))
	{
		std::cout << "Font loaded!" << std::endl;
	}
}
