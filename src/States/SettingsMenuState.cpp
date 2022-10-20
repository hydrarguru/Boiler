#include "SettingsMenuState.h"



SettingsMenuState::SettingsMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->InitFont();
	this->InitBackground();
	this->InitGUI();
	this->ReadSettings();
}

SettingsMenuState::~SettingsMenuState()
{

}

void SettingsMenuState::InitBackground()
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

void SettingsMenuState::InitFont()
{
	if (!this->font.loadFromFile(ENGINE_FONT))
	{
		throw("ERROR::SettingsMenuState::COULD NOT LOAD FONT");
	}
	std::cout << "SettingsMenuState::Loaded Fonts" << std::endl;
}

void SettingsMenuState::InitGUI()
{
	#pragma region Buttons
	/*
	buttonList[1] = new Button(10, 10, 200, 75,
		&this->font, "Main Menu",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	*/
	#pragma endregion
}

void SettingsMenuState::ReadSettings()
{
	if (std::filesystem::exists("engine.ini"))
	{
		mINI::INIFile file("engine.ini");
		mINI::INIStructure ini;
		file.read(ini);
		windowTitle = ini["Engine"]["w_title"];
		windowHeight = std::stoi(ini["Engine"]["w_height"]);
		windowWidth = std::stoi(ini["Engine"]["w_width"]);
		vsyncEnabled = std::stoi(ini["Engine"]["w_vsync"]);
		fullscreenEnabled = std::stoi(ini["Engine"]["w_fullscreen"]);
		framerate = std::stoi(ini["Engine"]["w_framerate"]);
		antialiasing = std::stoi(ini["Engine"]["w_antialiasing"]);
	}
}

void SettingsMenuState::ApplySettings()
{
	if (std::filesystem::exists("engine.ini"))
	{
		std::cout << "Changing Settings" << std::endl;
		mINI::INIFile file("engine.ini");
		mINI::INIStructure config;
		config["Engine"]["w_height"] = std::to_string(windowHeight);
		config["Engine"]["w_width"] = std::to_string(windowWidth);
		config["Engine"]["w_vsync"] = std::to_string(vsyncEnabled);
		config["Engine"]["w_fullscreen"] = std::to_string(fullscreenEnabled);
		config["Engine"]["w_framerate"] = std::to_string(framerate);
		config["Engine"]["w_antialiasing"] = std::to_string(antialiasing);
		file.generate(config, true);
	}
	else
		std::cout << "Failed to apply new settings. \n";


	std::cout << windowWidth << "\n";
	std::cout << windowHeight << "\n";
	std::cout << framerate << "\n";
	std::cout << antialiasing << "\n";
	std::cout << fullscreenEnabled << "\n";
	std::cout << vsyncEnabled << "\n";
}

void SettingsMenuState::UpdateInput(const float& dt)
{
	/*handling inputs and stuff*/
}

void SettingsMenuState::UpdateButtonEvent()
{
	/*
	for (auto &button : buttonList)
		button.second->Update(this->mousePosView);
	*/
}

void SettingsMenuState::RenderGUI(sf::RenderTarget* target)
{
	/*
	for (auto& button : this->buttonList)
		button.second->Render(target);

	for (auto& label : this->labelList)
		label.second->Render(target);
	*/
}

void SettingsMenuState::RenderImgui()
{
	static int s_windowHeight = windowHeight;
	static int s_windowWidth = windowWidth;
	static int s_framerate = framerate;
	static int s_antialiasing = antialiasing;
	static bool s_fullscreen = fullscreenEnabled;
	static bool s_vsync = vsyncEnabled;

	ImGui::ShowDemoWindow();
	ImGui::Begin("Settings");
	if (ImGui::InputInt("Window Width", &s_windowWidth, 0, 0)) { windowWidth = s_windowWidth; }
	if (ImGui::InputInt("Window Height", &s_windowHeight, 0, 0)) { windowHeight = s_windowHeight; }
	if (ImGui::InputInt("Framerate Limit", &s_framerate, 0, 0)) { framerate = s_framerate; }
	if (ImGui::InputInt("Anti Aliasing(1-4)", &s_antialiasing, 0, 0)) { antialiasing = s_antialiasing; }
	if (ImGui::Checkbox("Fullscreen", &s_fullscreen)) { fullscreenEnabled = s_fullscreen; }
	if (ImGui::Checkbox("VSync", &s_vsync)) { vsyncEnabled = s_vsync; }

	if (ImGui::Button("Apply Settings")) { ApplySettings(); }
	ImGui::Separator();
	if (ImGui::Button("Return to Main Menu")) { EndState(); }
	ImGui::End();
	ImGui::SFML::Render(*this->window);
}

void SettingsMenuState::Update(const float& dt)
{
	ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->UpdateButtonEvent();
}

void SettingsMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	RenderGUI(target);
	RenderImgui(); //ensures imgui windows are rendered on top of of other gui elements.
}