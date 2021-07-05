#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->InitImGui();
	this->InitFont();
	this->InitBackground();
	this->InitKeybinds();
	this->InitGUI();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::InitImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();
	ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(ctx);
}

void MainMenuState::InitBackground()
{
	
	if (!windowIcon.loadFromFile("Resources/Images/boiler_icon.png"))
	{
		throw("ERROR::MainMenuState::COULD_NOT_LOAD_ICON");
	}
	std::cout << "MainMenuState::LOADED_WINDOW_ICON" << std::endl;
	this->window->setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

	if (showBackground)
	{
		this->background.setSize(sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y))
		);
		if (!this->backgroundTexture.loadFromFile("Resources/Images/lab.jpg"))
			throw("MAINMENU:ERROR: COULD NOT LOAD BACKGROUND IMAGE");
		this->background.setTexture(&backgroundTexture);
	}
	else
	{
		this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
		this->background.setFillColor(sf::Color::Black);
		color[0] = background.getFillColor().r;
		color[1] = background.getFillColor().g;
		color[2] = background.getFillColor().b;
	}
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile("Fonts/VCR.ttf"))
	{
		throw("ERROR::MainMenuState::COULD NOT LOAD FONT");
	}
	std::cout << "MainMenuState::Loaded Fonts" << std::endl;
}

void MainMenuState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("CLOSE");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("MOVE_LEFT");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("MOVE_RIGHT");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("MOVE_UP");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("MOVE_DOWN");
}

void MainMenuState::InitGUI()
{
	#pragma region Buttons
	this->buttons["GAME_STATE"] = new Button(10, 10, 200, 75,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS_STATE"] = new Button(10, 90, 200, 75,
		&this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(10, 170, 200, 75,
		&this->font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	#pragma endregion
	#pragma region Labels
	//this->labels["MainMenu"] = new Label(700, 10, "Main Menu", &this->font, 72, WHITE, BLACK);
	//this->labels["test"] = new Label(690, 150, "test", &this->font, 64, sf::Color::Cyan, BLACK);
	#pragma endregion
}

void MainMenuState::UpdateInput(const float& dt)
{
}

void MainMenuState::UpdateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->Update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->IsPressed()) //Exit the Application
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["SETTINGS_STATE"]->IsPressed())
	{
		std::cout << "Settings Button" << std::endl;
	}

	if (this->buttons["EXIT_STATE"]->IsPressed()) //Exit the Application
	{
		this->EndState();
	}
}

void MainMenuState::RenderGUI(sf::RenderTarget* target)
{
	#pragma region Buttons
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
	#pragma endregion

	#pragma region Labels
	for (auto& it : this->labels)
	{
		it.second->Render(target);
	}
	#pragma endregion

}

void MainMenuState::Update(const float& dt)
{
	ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->UpdateButtons();
}

void MainMenuState::RenderImGUI(sf::RenderTarget* target)
{
	std::stringstream mousePos;
	mousePos << "Mouse Position: " << "X: " << this->mousePosView.x << " " << "Y: " << this->mousePosView.y;
	#pragma region ImGuiWindow
	ImGui::ShowDemoWindow(&SHOW_MENU);
	ImGui::Begin("Main Menu State", &SHOW_MENU, ImGuiWindowFlags_MenuBar);
	#pragma region MenuBar
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Start Game")) { this->states->push(new GameState(this->window, this->supportedKeys, this->states)); }
			if (ImGui::MenuItem("End App")) { this->EndState(); }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	#pragma endregion
	ImGui::Text("%.f FPS", ImGui::GetIO().Framerate); /*Display Framerate*/
	ImGui::SameLine(75);
	ImGui::Text(mousePos.str().c_str()); /*Display Mouse position*/
	ImGui::Separator();
	if (ImGui::ColorEdit3("Color", color))
	{
		bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
		bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
		bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		background.setFillColor(bgColor);
	}
	if (ImGui::Button("Set Main Menu Texture"))
	{
		if (!this->backgroundTexture.loadFromFile("Resources/Images/lab.jpg"))
			throw("MAINMENU:ERROR: COULD NOT LOAD BACKGROUND IMAGE");
		this->background.setTexture(&backgroundTexture);
	}
	ImGui::SameLine(175);
	if (ImGui::Button("Unload Texture")) { this->background.setTexture(nullptr); }
	ImGui::Separator();

	#pragma region Settings
	if (ImGui::CollapsingHeader("Config/Engine Settings"))
	{
		mINI::INIFile engine_cfg("config/engine.ini");
		mINI::INIStructure ini;
		engine_cfg.read(ini);
		std::string resolution_w = ini["ENGINE"]["window_width"];
		std::string resolution_h = ini["ENGINE"]["window_height"];

		ImGui::Text("Current Settings:");
		ImGui::Text("Window Height: ");
		ImGui::SameLine(110);
		ImGui::Text(resolution_h.c_str());

		ImGui::Text("Window Width: ");
		ImGui::SameLine(110);
		ImGui::Text(resolution_w.c_str());
	}
	#pragma endregion

	ImGui::End();
	#pragma endregion
	ImGui::SFML::Render(*target);
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->RenderGUI(target);
	this->RenderImGUI(target);
}