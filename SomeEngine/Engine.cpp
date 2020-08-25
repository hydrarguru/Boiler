#include "Engine.h"

void Engine::initWindow(const int WIDTH, const int HEIGHT, const std::string windowTitle)
{
	this->window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), windowTitle);
	std::cout << "Boiler initialized" << std::endl;
	loadFont();
}

Engine::Engine()
{
	initWindow(1280, 720, "Boiler");
}
Engine::~Engine()
{
	delete this->window;
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
