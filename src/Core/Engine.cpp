#include "Engine.h"

void Engine::InitWindow()
{
	sf::VideoMode windowBounds = sf::VideoMode::getDesktopMode();

	if (!std::filesystem::exists(ENGINE_CONFIG))
	{
		this->window = new sf::RenderWindow(sf::VideoMode(window_height, window_width), windowTitle, sf::Style::Resize);
		this->window->setFramerateLimit(framerate);
	}
	else
	{
		mINI::INIFile file(ENGINE_CONFIG);
		mINI::INIStructure ini;
		file.read(ini);

		windowTitle = ini["Engine"]["w_title"];
		window_height = std::stoi(ini["Engine"]["w_height"]);
		window_width = std::stoi(ini["Engine"]["w_width"]);

		vsync = std::stoi(ini["Engine"]["w_vsync"]);
		fullscreen = std::stoi(ini["Engine"]["w_fullscreen"]);
		framerate = std::stoi(ini["Engine"]["w_framerate"]);
		antialiasing = std::stoi(ini["Engine"]["w_antialiasing"]);

		windowBounds.height = window_height;
		windowBounds.width = window_width;
		this->windowSettings.antialiasingLevel = antialiasing;

		if (fullscreen)
		{

			this->window = new sf::RenderWindow(windowBounds, windowTitle, sf::Style::Fullscreen, this->windowSettings);
			this->window->setMouseCursorGrabbed(true);
		}
		else
			this->window = new sf::RenderWindow(windowBounds, windowTitle, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);

		this->window->setFramerateLimit(framerate);
		this->window->setVerticalSyncEnabled(vsync);
	}
}

void Engine::InitImGui()
{
	ImGui::SFML::Init(*this->window);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	if(std::filesystem::exists(ENGINE_FONT_ALT))
	{
		char* font = const_cast<char*>(ENGINE_FONT_ALT.c_str());
		io.Fonts->Clear();
		io.Fonts->AddFontFromFileTTF(font, 18.f);
		ImGui::SFML::UpdateFontTexture();
	}
	else
		io.Fonts->AddFontDefault();
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

void Engine::GenerateConfig()
{
	if (!std::filesystem::exists(ENGINE_CONFIG))
	{
		std::cout << "Generating config file..." << std::endl;
		INIFile file(ENGINE_CONFIG);
		INIStructure config;
		config["Engine"]["w_title"] = "Boiler";
		config["Engine"]["w_height"] = "1080";
		config["Engine"]["w_width"] = "1920";
		config["Engine"]["w_vsync"] = "1";
		config["Engine"]["w_fullscreen"] = "0";
		config["Engine"]["w_framerate"] = "60";
		config["Engine"]["w_antialiasing"] = "4";
		file.generate(config, true);
	}
}

Engine::Engine()
{
	GenerateConfig();
	InitWindow();
	InitImGui();
	InitState();
}

Engine::~Engine()
{
	delete this->window;
	while (!this->states.empty())
	{
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
