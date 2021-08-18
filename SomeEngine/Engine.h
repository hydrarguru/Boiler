#pragma once
#include "MainMenuState.h"

class Engine
{
private:
	/*Variables*/
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Image windowIcon;

	std::string windowTitle;
	int window_height;
	int window_width;
	bool vsync;
	bool fullscreen;
	unsigned framerate;
	unsigned antialiasing;


	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	sf::Clock dtClock;
	float dt;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;


	/*Init*/
	bool Configure();
	void InitImGui();
	void InitVariables();
	void InitWindow();
	void InitKeybinds();
	void InitState();

	/*Configs*/
	bool GenerateEngineConfig();
	bool GenerateKeyConfig();

public:
	//Constructor - Destructor
	Engine();
	virtual ~Engine();


	//Functions
	void ExitApplication();
	void ClearLog();

	//Update
	void UpdateDt();
	void UpdateSFMLEvents();
	void Update();

	//Render
	void Render();

	//Core
	void Run();
};
