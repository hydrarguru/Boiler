#include "GameState.h"
#include "MainMenuState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->InitFonts();
	this->InitVariables();
	this->InitKeybinds();
	this->InitTextures();
	this->InitPlayer();
	this->InitImGui();
	this->InitGUI();
}

GameState::~GameState()
{
	delete this->player;
	delete &this->textures;
}

void GameState::InitVariables()
{
	//Test Commit to development branch
}

void GameState::InitGUI()
{
	#pragma region Buttons
	this->buttons["MAIN_MENU_STATE"] = new Button(925, 10, 125, 50,
		&this->font, "Main Menu",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	#pragma endregion

	#pragma region Labels
	this->labels["PlayerHealth"] = new Label(1200, 10, "Player Health: " + std::to_string(player->GetHealth()), &this->font, 24);
	this->labels["PlayerSpeed"] = new Label(1200, 50, "Player Speed: " + std::to_string(player->GetMovementSpeed()), &this->font, 24);
	#pragma endregion
}

void GameState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("CLOSE");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("MOVE_LEFT");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("MOVE_RIGHT");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("MOVE_UP");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("MOVE_DOWN");
}

void GameState::InitTextures()
{
	this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Skeleton_Idle.png");
}

void GameState::InitPlayer()
{
	this->player = new Player(&this->textures["PLAYER_IDLE"], 10, 10);
}

void GameState::InitFonts()
{
	if (!this->font.loadFromFile(ENGINE_FONT))
	{
		throw("ERROR::GameState::COULD NOT LOAD FONT");
	}
	std::cout << "GameState::LOADED_FONT" << std::endl;
}

void GameState::InitImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();
	ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(ctx);
}

void GameState::RenderImGui(sf::RenderTarget* target)
{
	static int playerHealth = player->GetHealth();
	static float playerSpeed = player->GetMovementSpeed();
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Begin("GameState");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::CollapsingHeader("Player Settings"))
	{
		ImGui::PushItemWidth(100.f);
		ImGui::InputInt("Player Health", &playerHealth, 0, 1000);
		ImGui::SameLine();
		if (ImGui::Button("Set"))
		{
			player->SetPlayerHealth(playerHealth);
			this->labels.erase("PlayerHealth"); // Removes the element from the map
			this->labels["PlayerHealth"] = new Label(1200, 10, "Player Health: " + std::to_string(player->GetHealth()), &this->font, 24); // Adds new element to the map
		}

		if (ImGui::InputFloat("Player Speed", &playerSpeed, 10.f, 100.f))
		{
			player->SetSpeed(playerSpeed);
			this->labels.erase("PlayerSpeed"); // Removes the element from the map
			this->labels["PlayerSpeed"] = new Label(1200, 50, "Player Speed: " + std::to_string(player->GetMovementSpeed()), &this->font, 24); // Adds new element to the map
		}
	}


	ImGui::End();
	ImGui::SFML::Render(*target);
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
	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosView);
	}
	if (this->buttons["MAIN_MENU_STATE"]->IsPressed())
	{
		this->quit = true; //End GameState and goes back to MainMenuState
	}
}

void GameState::Update(const float& dt)
{
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->player->Update(dt);
	ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateButtons();
}

void GameState::RenderGUI(sf::RenderTarget* target)
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

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->player->Render(target);
	RenderGUI(target);
	RenderImGui(target);
}

