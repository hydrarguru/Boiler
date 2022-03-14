#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	/*Variables*/
	int playerHealth;
	sf::RectangleShape m_shape;

	/*Initializer Functions*/
	void InitVariables();
	void InitComponents();

public:
	Player(sf::Texture* texture, float x, float y);
	Player(float sizeX, float sizeY, float posX, float posY);
	~Player();
	/*Functions*/
	int GetHealth();
	float GetMovementSpeed();
	void SetSpeed(float speed);
	void SetPlayerHealth(int health);
};

