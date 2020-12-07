#include "GameState.h"
#include "MainMenuState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->initVars();
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
	this->initImGui();
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::initVars()
{
}

void GameState::initKeybinds()
{
	mINI::INIFile file("config/keys.ini");
	mINI::INIStructure ini;
	file.read(ini);

	this->keybinds["CLOSE"] = std::stoi(ini["GAME"]["Escape"]);
	this->keybinds["MOVE_LEFT"] = std::stoi(ini["GAME"]["D"]);
	this->keybinds["MOVE_RIGHT"] = std::stoi(ini["GAME"]["A"]);
	this->keybinds["MOVE_UP"] = std::stoi(ini["GAME"]["W"]);
	this->keybinds["MOVE_DOWN"] = std::stoi(ini["GAME"]["S"]);


	/*
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
	*/
}

void GameState::initTextures()
{
	this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Skeleton_Idle.png");
}

void GameState::initPlayers()
{
	this->player = new Player(&this->textures["PLAYER_IDLE"], 10, 10);
}

void GameState::initImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();
	ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(ctx);
}

void GameState::RenderImGui(sf::RenderTarget* target)
{
	ImGui::Begin("Game State Menu - Using ImGui");
	if (ImGui::Button("Go back to menu"))
	{
		this->quit = true;
	}
	bool show = true;
	ImGui::ShowDemoWindow(&show);
	ImGui::End();
	ImGui::SFML::Render(*target);
}

void GameState::updateInput(const float& dt)
{
	//Update Player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->Move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->Move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->Move(dt, 0.f, 1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::Update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->player->Update(dt);
	ImGui::SFML::Update(*this->window, dtClock.restart());
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->player->Render(target);
	RenderImGui(target);
}
