#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	DebugLog("Entered GameState");
	this->InitFont();
	this->InitPlayer();
	this->InitGUI();
}

GameState::~GameState()
{

}

void GameState::InitPlayer()
{
	this->textures["Player_Idle"].loadFromFile("images/Skeleton1.png");
	this->textures["Knight_Idle"].loadFromFile("../res/images/Knight/KnightIdle_strip.png");
	this->player = new Player(&textures["Knight_Idle"], 400, 600);
}

void GameState::InitFont()
{
	if (this->font.loadFromFile(ENGINE_FONT)) { DebugLog("GameState::Loaded Fonts"); }
}

void GameState::InitGUI()
{
	buttonList[1] = new Button(1000, 90, 100, 50, &font, "Hey", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
	buttonList[2] = new Button(1200, 90, 100, 50, &font, "From", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
	buttonList[3] = new Button(1400, 90, 100, 50, &font, "Gamestate", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
}

void GameState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::A)))
		this->player->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::D)))
		this->player->Move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::W)))
		this->player->Move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::S)))
		this->player->Move(dt, 0.f, 1.f);
}

void GameState::UpdateButtonEvent()
{
	for (auto& button : buttonList)
	{
		button.second->Update(this->mousePosView);
	}
}

void GameState::RenderImgui()
{
	static int pHealth = player->GetHealth();
	static float pVel = player->GetPlayerVeloctity();
	float vel = 0.f;
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("GameState - Imgui");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Separator();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("Player Health", &pHealth, 0, 1000);
	ImGui::SameLine();
	if (ImGui::Button("Set")) { player->SetPlayerHealth(pHealth); }
	ImGui::Separator();
	if (ImGui::InputFloat("Player Velocity", &pVel, 10.f, 100.f)) { vel = pVel; }
	if (ImGui::Button("Set")) { player->SetPlayerVelocity(vel); }
	ImGui::Separator();

	if (ImGui::Button("Quit")) { this->quit = true; }
	ImGui::End();
	ImGui::SFML::Render(*this->window);
}

void GameState::RenderGUI(sf::RenderTarget* target)
{
	for (auto& button : this->buttonList) { button.second->Render(target); }
}

void GameState::Update(const float& dt)
{
	ImGui::SFML::Update(*this->window, dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->player->Update(dt);
	this->UpdateButtonEvent();
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->player->Render(target);
	this->RenderGUI(target);
	RenderImgui();
}