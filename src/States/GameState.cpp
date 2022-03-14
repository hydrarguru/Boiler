#include "GameState.h"
#include "MainMenuState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->InitFonts();
	this->InitTextures();
	this->InitPlayer();
	this->InitGUI();
}

GameState::~GameState()
{
	//delete this->player;
	//delete &this->textures;
}

void GameState::InitGUI()
{
	#pragma region Buttons
	buttonList[1] = new Button(925, 10, 125, 50,
		&this->font, "Main Menu",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	#pragma endregion
}

void GameState::InitTextures()
{
	DebugLog("GameState::InitTextures");
	//this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Skeleton_Idle.png");
}

void GameState::InitPlayer()
{
	//this->player = new Player(&this->textures["PLAYER_IDLE"], 10, 10);
	//this->player = new Player(50, 50, 10, 10);
}

void GameState::InitFonts()
{
	if (!this->font.loadFromFile(ENGINE_FONT)){	std::cout << "ERROR::GameState::COULD NOT LOAD FONT" << std::endl; }
	else
		std::cout << "GameState::LOADED_FONT" << std::endl;
}

void GameState::UpdateInput(const float& dt)
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
		this->EndState();
}

void GameState::UpdateButtons()
{
	for (auto& it : this->buttonList)
	{
		it.second->Update(this->mousePosView);
	}
	if (this->buttonList[1]->IsPressed())
	{
		this->quit = true; //End GameState and goes back to MainMenuState
	}
}

void GameState::Update(const float& dt)
{
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->player->Update(dt);
	//ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateButtons();
}

void GameState::RenderGUI(sf::RenderTarget* target)
{
	#pragma region Buttons
	for (auto& it : this->buttonList)
	{
		it.second->Render(target);
	}
	#pragma endregion
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->player->Render(target);
	RenderGUI(target);
	//RenderImGui(target);
}

