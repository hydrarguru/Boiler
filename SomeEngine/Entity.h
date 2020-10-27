#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <map>

//SFML
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

//ImGui
#include <ImGui/imgui.h>
#include <ImGuiSFML/imgui-SFML.h>


class Entity
{
private:

protected:
	
public:
	Entity();
	virtual ~Entity();
	/*Variables*/
	sf::CircleShape shape;
	sf::Color playerColor;
	float movementSpeed;

	/*Functions*/
	virtual void Move(const float& dt, const float x, const float y);
	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget* target);
};