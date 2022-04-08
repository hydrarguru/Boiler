#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->InitFont();
	this->InitPlayer();
	this->InitGUI();
}

GameState::~GameState()
{

}

void GameState::InitPlayer()
{
	this->textures["Knight_Attack"].loadFromFile("../res/images/Knight/KnightAttack.png");
	this->textures["Knight_Death"].loadFromFile("../res/images/Knight/KnightDeath.png");
	this->textures["Knight_Idle"].loadFromFile("../res/images/Knight/KnightIdle.png");
	this->textures["Knight_JumpFall"].loadFromFile("../res/images/Knight/KnightJumpFall.png");
	this->textures["Knight_Roll"].loadFromFile("../res/images/Knight/KnightRoll.png");
	this->textures["Knight_Run"].loadFromFile("../res/images/Knight/KnightRun.png");
	this->textures["Knight_Shield"].loadFromFile("../res/images/Knight/KnightShield.png");
	this->m_player = new Player(&textures["Knight_Idle"], 400, 600);
}

void GameState::InitFont()
{
	if (this->m_font.loadFromFile(ENGINE_FONT)) { DebugLog("GameState::Loaded Fonts"); }
}

void GameState::InitGUI()
{
	m_buttonList[1] = new Button(1000, 90, 100, 50, &m_font, "Hey", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
	m_buttonList[2] = new Button(1200, 90, 100, 50, &m_font, "From", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
	m_buttonList[3] = new Button(1400, 90, 100, 50, &m_font, "Gamestate", sf::Color(25, 50, 125, 255), sf::Color(70, 70, 70, 200),sf::Color(20, 20, 20, 200));
}

void GameState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::A)))
		this->m_player->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::D)))
		this->m_player->Move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::W)))
		this->m_player->Move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sf::Keyboard::S)))
		this->m_player->Move(dt, 0.f, 1.f);
}

void GameState::UpdateButtonEvent()
{
	for (auto& button : m_buttonList)
	{
		button.second->Update(this->mousePosView);
	}
}

void GameState::RenderImgui()
{
	static int pHealth = m_player->GetHealth();
	static float pVel = m_player->GetPlayerVeloctity();
	static int spriteFrame = 1;
	float vel = 0.f;
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Begin("GameState - Imgui");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::Separator();
	ImGui::PushItemWidth(100.f);
	ImGui::InputInt("Player Health", &pHealth, 0, 1000);
	ImGui::SameLine();
	if (ImGui::Button("Set")) { m_player->SetPlayerHealth(pHealth); }
	ImGui::Separator();
	if (ImGui::InputFloat("Player Velocity", &pVel, 10.f, 100.f)) { vel = pVel; }
	if (ImGui::Button("Set")) { m_player->SetPlayerVelocity(vel); }
	ImGui::Separator();
	if(ImGui::InputInt("Set Sprite #", &spriteFrame, 1, 1))
	{
		m_player->SetSprite(960, 15, spriteFrame);
	}
	if (ImGui::Button("Test Sprite"))
	{
		int i = 1;
		i++;
		m_player->SetSprite(960, 15, i);
	}
	ImGui::Separator();
	if (ImGui::Button("Quit")) { this->quit = true; }
	ImGui::End();
	ImGui::SFML::Render(*this->window);
}

void GameState::RenderGUI(sf::RenderTarget* target)
{
	for (auto& button : this->m_buttonList) { button.second->Render(target); }
}

void GameState::Update(const float& dt)
{
	ImGui::SFML::Update(*this->window, m_dtClock.restart());
	this->UpdateMousePosition();
	this->UpdateInput(dt);
	this->m_player->Update(dt);
	this->UpdateButtonEvent();
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->m_background);
	this->m_player->Render(target);
	this->RenderGUI(target);
	RenderImgui();
}