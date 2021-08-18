#include "Engine.h"

bool Engine::GenerateEngineConfig()
{
	mINI::INIFile file("config/engine.ini");
	DebugLog("Could not load config. Generating new config.");
	mINI::INIFile config("engine.ini");
	mINI::INIStructure ini;
	ini["ENGINE"]["window_name"] = "Boiler";
	ini["ENGINE"]["window_height"] = "1080";
	ini["ENGINE"]["window_width"] = "1920";
	ini["DISPLAY"]["vsync"] = "1";
	ini["DISPLAY"]["fullscreen"] = "1";
	ini["DISPLAY"]["framerate"] = "144";
	ini["DISPLAY"]["antialiasing"] = "0";
	if (file.generate(ini, true))
		return true;
	else
		return false;
}

bool Engine::GenerateKeyConfig()
{
	mINI::INIFile file("config/keys.ini");
	DebugLog("Could not load key config. Generating new key config.");
	mINI::INIFile config("keys.ini");
	mINI::INIStructure ini;
	ini["GAME"]["A"] = "0";
	ini["GAME"]["D"] = "3";
	ini["GAME"]["W"] = "22";
	ini["GAME"]["S"] = "18";
	ini["GAME"]["Escape"] = "36";
	if (file.generate(ini, true))
		return true;
	else
		return false;
}

bool Engine::Configure()
{
	mINI::INIFile config("config/engine.ini");
	mINI::INIStructure ini;
	if (!config.read(ini))
		GenerateEngineConfig();
	else
	{
		DebugLog("Engine::LOADED_CONFIG");
		return true;
	}
	return false;
}

void Engine::InitWindow()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
	sf::VideoMode windowBounds = sf::VideoMode::getDesktopMode();

	mINI::INIFile file("config/engine.ini");
	mINI::INIStructure ini;
	file.read(ini);


	/*ENGINE*/
	windowTitle = ini["ENGINE"]["window_name"];
	window_height = std::stoi(ini["ENGINE"]["window_height"]);
	window_width = std::stoi(ini["ENGINE"]["window_width"]);

	/*DISPLAY*/
	vsync = std::stoi(ini["DISPLAY"]["vsync"]);
	fullscreen = std::stoi(ini["DISPLAY"]["fullscreen"]);
	framerate = std::stoi(ini["DISPLAY"]["framerate"]);
	antialiasing = std::stoi(ini["DISPLAY"]["antialiasing"]);

	windowBounds.height = window_height;
	windowBounds.width = window_width;
	this->windowSettings.antialiasingLevel = antialiasing;

	if (this->fullscreen)
		this->window = new sf::RenderWindow(windowBounds, windowTitle, sf::Style::None, this->windowSettings);
	else
		this->window = new sf::RenderWindow(windowBounds, windowTitle, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

	this->window->setFramerateLimit(framerate);
	this->window->setVerticalSyncEnabled(vsync);
}

void Engine::InitImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();	
}

void Engine::InitVariables()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0;
}

void Engine::InitKeybinds()
{
	mINI::INIFile keys("config/keys.ini");
	mINI::INIStructure ini;
	if (!keys.read(ini))
		GenerateKeyConfig();

	keys.read(ini);
	this->supportedKeys["CLOSE"] = std::stoi(ini["GAME"]["Escape"]);
	this->supportedKeys["MOVE_LEFT"] = std::stoi(ini["GAME"]["A"]);
	this->supportedKeys["MOVE_RIGHT"] = std::stoi(ini["GAME"]["D"]);
	this->supportedKeys["MOVE_UP"] = std::stoi(ini["GAME"]["W"]);
	this->supportedKeys["MOVE_DOWN"] = std::stoi(ini["GAME"]["S"]);
	DebugLog("Engine::LOADED_KEYBINDINGS");
}

void Engine::InitState()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Engine::Engine()
{
	if (this->Configure()) //checks if a config exist, otherwise generate a new one and keep the application run.
	{
		this->InitWindow();
		this->InitImGui();
		this->InitKeybinds();
		this->InitState();
	}
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

void Engine::UpdateSFMLEvents()
{
	while (this->window->pollEvent(sfEvent)) 
	{
		ImGui::SFML::ProcessEvent(sfEvent);
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
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->ExitApplication();
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
	ImGui::SFML::Shutdown();
}

void Engine::ExitApplication()
{
	DebugLog("Engine::BOILER_SHUTDOWN");
}
