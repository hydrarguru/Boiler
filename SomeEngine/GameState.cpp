#include "GameState.h"
#include "MainMenuState.h"


GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->initVars();
	this->initKeybinds();
	this->initImGui();
}

GameState::~GameState()
{

}

void GameState::initVars()
{
	movementSpeed = Player.getMovementSpeed();
	color[0] = Player.getPlayerShape().getFillColor().r;
	color[1] = Player.getPlayerShape().getFillColor().g;
	color[2] = Player.getPlayerShape().getFillColor().b;
}

void GameState::initKeybinds()
{
	std::ifstream ifs("gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();


	this->keybinds["QUIT"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void GameState::RenderImGui(sf::RenderTarget* target)
{
	ImGui::Begin("Game State Menu - Using ImGui");
	if (ImGui::ColorEdit3("Player Color", color)) 
	{
		bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
		bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
		bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		Player.setPlayerShapeColor(bgColor);
	}
	ImGui::Text("Player Speed: %.f", Player.getMovementSpeed());
	ImGui::InputFloat("Change Player Speed", &movementSpeed, 50.f);
	if (ImGui::Button("Set player speed"))
	{
		Player.setMovementSpeed(movementSpeed);
	}

	if (ImGui::Button("Go back to menu"))
	{
		this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states));
	}
	ImGui::End();
	ImGui::SFML::Render(*target);
}

void GameState::initImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();
	ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(ctx);
	ImGui::StyleColorsDark();
}

void GameState::endState()
{
	std::cout << "Ending GameState" << std::endl;
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
	//Update Player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->Player.Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->Player.Move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->Player.Move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->Player.Move(dt, 0.f, 1.f);
}

void GameState::Update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->Player.Update(dt);
	ImGui::SFML::Update(*this->window, dtClock.restart());
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->Player.Render(target);
	RenderImGui(target);
}
