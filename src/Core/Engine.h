#pragma once
#include "Core/boiler.h"
#include "States/State.h"
#include "States/MainMenuState.h"

class Engine
{
private:
	/*Variables*/
	sf::RenderWindow* window;
	sf::Event sfEvent;

	std::string windowTitle = "Boiler";
	int window_height = 1920;
	int window_width = 1080;
	unsigned framerate = 60;
	bool vsync;
	bool fullscreen;
	unsigned antialiasing;


	sf::ContextSettings windowSettings;
	sf::Clock dtClock;
	float dt;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;


	/*Init*/

	void InitImGui();
	void InitVariables();
	void InitWindow();
	void InitState();

	/*Configs*/
	void GenerateConfig();

public:
	//Constructor - Destructor
	Engine();
	virtual ~Engine();

	//Update
	void UpdateDt();
	void UpdateSFMLEvents();
	void Update();

	//Render
	void Render();

	//Core
	void Run();
};
