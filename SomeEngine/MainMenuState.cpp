#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initImGui();
	this->initVars();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::initImGui()
{
	ImGui::SFML::Init(*this->window);
	this->window->resetGLStates();
	ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(ctx);
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f
	(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);
	if (!this->backgroundTexture.loadFromFile("Resources/Images/lab.jpg"))
		throw("MAINMENU:ERROR: COULD NOT LOAD BACKGROUND IMAGE");
	this->background.setTexture(&backgroundTexture);
}

void MainMenuState::initVars()
{
	/*stuff not used atm
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::White);
	color[0] = background.getFillColor().r;
	color[1] = background.getFillColor().g;
	color[2] = background.getFillColor().b;
	*/
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Roboto.ttf"))
	{
		throw("ERROR::MainMenuState::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("mainmenustate_keybinds.ini");
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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(10, 10, 200, 75,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS_STATE"] = new Button(10, 90, 200, 75,
		&this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(10, 170, 200, 75,
		&this->font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState" << std::endl;
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->Update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed()) //Exit the Application
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EXIT_STATE"]->isPressed()) //Exit the Application
	{
		this->quit = true;
	}
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->Render(target);
	}
}

void MainMenuState::Update(const float& dt)
{
	ImGui::SFML::Update(*this->window, dtClock.restart());
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::RenderImGUI(sf::RenderTarget* target)
{
	ImGui::Begin("Main Menu - Using ImGui");
	if (ImGui::ColorEdit3("Background color", color)) {
		bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
		bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
		bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		//background.setFillColor(bgColor);
	}
	ImGui::End();
	ImGui::SFML::Render(*target);
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderButtons(target);
	this->RenderImGUI(target);

	if (SHOW_MOUSE_POS_DEBUG)
	{
		sf::Text mouseText;
		mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 15);
		mouseText.setFont(this->font);
		mouseText.setCharacterSize(18);
		std::stringstream ss;
		ss << "X: " << this->mousePosView.x << " | " << "Y: " << this->mousePosView.y;
		mouseText.setString(ss.str());
		target->draw(mouseText);
	}
}