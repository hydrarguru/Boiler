#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	InitFonts();
	InitTextures();
	InitGUI();
}

GameState::~GameState()
{
	//delete &this->textures;
}


void GameState::InitGUI()
{
	buttonList[1] = new Button(100.f, 100.f, 100.f, 50.f, &font, "Hello!", sf::Color::Blue, sf::Color::Green, sf::Color::Yellow);
}


void GameState::InitTextures()
{
	//this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Skeleton_Idle.png");
}

void GameState::InitFonts()
{
    font.loadFromFile(ENGINE_FONT);
	DebugLog("GameState::LOADED_FONT");
}

void GameState::UpdateInput(const float& dt)
{
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->Move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->Move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->Move(dt, 0.f, 1.f);
    */
}

void GameState::UpdateButtons()
{

}

void GameState::Update(const float& dt)
{
	UpdateMousePosition();
	UpdateInput(dt);
    UpdateButtons();
	//player->Update(dt);
}

void GameState::RenderGUI(sf::RenderTarget* target)
{
	buttonList[1]->Render(target);
}


void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	//this->player->Render(target);
	RenderGUI(target);
}