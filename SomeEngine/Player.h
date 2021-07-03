#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	/*Variables*/
	int playerHealth;

	/*Initializer Functions*/
	void initVars();
	void initComponents();

public:
	Player(sf::Texture* texture, float x, float y);
	virtual ~Player();
	/*Functions*/
	int GetHealth();
	float GetMovementSpeed();
	void SetSpeed(float speed);
	void SetPlayerHealth(int health);
};

