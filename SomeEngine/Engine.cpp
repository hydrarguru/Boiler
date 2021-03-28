#include "Engine.h"

bool Engine::Configure()
{
	mINI::INIFile file("config/engine.ini");
	mINI::INIStructure ini;
	if (!file.read(ini))
	{
		std::cout << "Could not load config. Generating new config." << std::endl;

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
	else
		std::cout << "loaded config" << std::endl;
}

void Engine::initWindow()
{
	//Window Icon
	if (!windowIcon.loadFromFile("Resources/Images/boiler_icon.png"))
	{
		throw("ERROR::MainMenuState::COULD_NOT_LOAD_ICON");
	}
	std::cout << "Engine::LOADED_WINDOW_ICON" << std::endl;
	this->window->setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

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

void Engine::initImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();	
}

void Engine::initVars()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0;
}

void Engine::initKeys()
{
	mINI::INIFile file("config/keys.ini");
	mINI::INIStructure ini;
	file.read(ini);

	this->supportedKeys["CLOSE"] = std::stoi(ini["GAME"]["Escape"]);
	this->supportedKeys["MOVE_LEFT"] = std::stoi(ini["GAME"]["A"]);
	this->supportedKeys["MOVE_RIGHT"] = std::stoi(ini["GAME"]["D"]);
	this->supportedKeys["MOVE_UP"] = std::stoi(ini["GAME"]["W"]);
	this->supportedKeys["MOVE_DOWN"] = std::stoi(ini["GAME"]["S"]);
	std::cout << "Loaded Keybindings" << std::endl;
}

void Engine::initState()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Engine::Engine()
{
	if (this->Configure()) //checks if a config exist, otherwise generate a new one and keep the application run.
	{
		this->initWindow();
		this->initImGui();
		this->initKeys();
		this->initState();
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

void Engine::updateSFMLEvents()
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

void Engine::endApp()
{
	std::cout << "Boiler Shutdown" << std::endl;
}
