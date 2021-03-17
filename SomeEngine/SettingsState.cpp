#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{

}

SettingsState::~SettingsState()
{

}
