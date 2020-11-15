#include "Engine.h"

bool Engine::initConfig()
{
	mINI::INIFile file("config/engine.ini");
	mINI::INIStructure ini;
	if (!file.read(ini))
	{
		std::cout << "Could not load config." << std::endl;
		std::cout << "Generating new config." << std::endl;

		mINI::INIFile config("engine.ini");
		mINI::INIStructure ini;
		ini["ENGINE"]["window_name"] = "generatedconfigtest";
		ini["ENGINE"]["window_height"] = "1080";
		ini["ENGINE"]["window_width"] = "1920";
		ini["DISPLAY"]["vsync"] = "1";
		ini["DISPLAY"]["fullscreen"] = "1";
		ini["DISPLAY"]["framerate"] = "144";
		ini["DISPLAY"]["antialiasing"] = "0";
		if (file.generate(ini, true))
		{
			return true;
		}
		else
			return false;
	}
}

void Engine::initWindow()
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

void Engine::initImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();
	/*
	ImGuiIO IO = ImGui::GetIO();
	IO.Fonts->Clear();
	IO.Fonts->AddFontFromFileTTF("Roboto.ttf", 18.f);
	ImGui::SFML::UpdateFontTexture();
	*/
}

void Engine::initVars()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0;
}

void Engine::initKeys()
{
	std::ifstream ifs("supported_keys.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();

	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Engine::initState()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Engine::Engine()
{
	if (this->initConfig())
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
