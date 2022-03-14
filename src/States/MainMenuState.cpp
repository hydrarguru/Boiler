#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->InitFont();
	this->InitBackground();
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

void MainMenuState::InitBackground()
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
	color[0] = background.getFillColor().r;
	color[1] = background.getFillColor().g;
	color[2] = background.getFillColor().b;
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
	/*handling inputs and stuff*/
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
		//std::cout << "Settings Button" << std::endl;
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
	//ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->UpdateButtons();
}


void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->RenderGUI(target);
	//this->RenderImGUI(target);
}