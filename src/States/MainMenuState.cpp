#include "MainMenuState.h"



MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	DebugLog("Entered MainMenuState");
	this->InitFont();
	this->InitBackground();
	this->InitImgui();
	this->InitGUI();
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::InitImgui()
{
	ImGui::SFML::Init(*this->window);
	ImGuiIO io = ImGui::GetIO();
	if(std::filesystem::exists(ENGINE_FONT_ALT))
	{
		io.Fonts->Clear();
		io.Fonts->AddFontFromFileTTF(ENGINE_FONT_ALT, 16);
		ImGui::SFML::UpdateFontTexture();
	}
	else
		io.Fonts->AddFontDefault();
}

void MainMenuState::InitBackground()
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile(ENGINE_FONT))
	{
		throw("ERROR::MainMenuState::COULD NOT LOAD FONT");
	}
	DebugLog("MainMenuState::Loaded Fonts");
}

void MainMenuState::InitGUI()
{
	#pragma region Buttons
	buttonList[1] = new Button(10, 10, 200, 75,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttonList[2] = new Button(10, 90, 200, 75,
		&this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttonList[3] = new Button(10, 170, 200, 75,
		&this->font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	#pragma endregion
}

void MainMenuState::UpdateInput(const float& dt)
{
	/*handling inputs and stuff*/
}

void MainMenuState::UpdateButtonEvent()
{
	for (auto &button : buttonList)
	{
		button.second->Update(this->mousePosView);
	}

	if (this->buttonList[1]->IsPressed()) //Exit the Application
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttonList[1]->IsPressed())
	{
		//std::cout << "Settings Button" << std::endl;
	}

	if (this->buttonList[1]->IsPressed()) //Exit the Application
	{
		this->EndState();
	}
}

void MainMenuState::RenderGUI(sf::RenderTarget* target)
{
	#pragma region Buttons
	for (auto& button : this->buttonList)
	{
		button.second->Render(target);
	}
	#pragma endregion

	#pragma region Labels
	for (auto& label : this->labelList)
	{
		label.second->Render(target);
	}
	#pragma endregion

}

void MainMenuState::RenderImgui()
{
	ImGui::ShowDemoWindow();
	ImGui::Begin("sdasd");
	ImGui::Text("asdasd");
	ImGui::End();
	ImGui::SFML::Render(*this->window);
}

void MainMenuState::Update(const float& dt)
{
	ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->UpdateButtonEvent();
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	RenderGUI(target);
	RenderImgui(); //ensures imgui windows are rendered on top of of other gui elements.
}