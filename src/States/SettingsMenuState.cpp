#include "SettingsMenuState.h"



SettingsMenuState::SettingsMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->InitFont();
	this->InitBackground();
	this->InitGUI();
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
	buttonList[1] = new Button(10, 10, 200, 75,
		&this->font, "Main Menu",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	#pragma endregion
}

void SettingsMenuState::UpdateInput(const float& dt)
{
	/*handling inputs and stuff*/
}

void SettingsMenuState::UpdateButtonEvent()
{
	for (auto &button : buttonList)
		button.second->Update(this->mousePosView);

	if (this->buttonList[1]->IsPressed())
		this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states));
}

void SettingsMenuState::RenderGUI(sf::RenderTarget* target)
{
	for (auto& button : this->buttonList)
		button.second->Render(target);

	for (auto& label : this->labelList)
		label.second->Render(target);
}

void SettingsMenuState::RenderImgui()
{
	ImGui::ShowDemoWindow();
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